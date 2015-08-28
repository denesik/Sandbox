// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "World.h"
#include "..\Graphic\RegistryGraphic.h"
#include "..\RegistryCore.h"


World::World()
{
}


World::~World()
{
}

void World::LoadSector(const glm::ivec3 &pos)
{
  // Проверяем, загружен ли сектор.

  const auto sector = mMap.find(pos);
  if (sector == mMap.end())
  {
    // Не нашли сектор, создадим его.
    mMap.emplace(pos, pos);
  }
  else
  {
    ++sector->second.refCount;
  }
}

void World::UnloadSector(const glm::ivec3 &pos)
{
  const auto sector = mMap.find(pos);
  if (sector != mMap.end())
  {
    if (sector->second.refCount)
    {
      --sector->second.refCount;
      if (!sector->second.refCount)
      {
        sector->second.timer.Start();
      }
    }
  }
}

void World::Update()
{
  for (auto &i : mPlayers)
  {
    i.sectorLoader.SetPos(GetSectorPos(i.player.GetPosition()));
  }

  for (auto sector = mMap.begin(); sector != mMap.end();)
  {
    /// Удаляем сектор, если счетчик ссылок == 0 и прошло заданное кол-во времени.
    if (!sector->second.refCount && sector->second.timer.Elapsed() > 1000)
    {
      sector = mMap.erase(sector);
    }
    else
    {
      ++sector;
    }
  }
}

void World::Draw()
{
  for (auto &sector : mMap)
  {
    REGISTRY_GRAPHIC.GetRender().DrawSector(sector.second.renderSector);
  }
}

void World::AddPlayer(Player &player)
{
  mPlayers.emplace_back(player, *this);
}

glm::ivec3 World::GetSectorPos(const glm::vec3 &pos)
{
  return glm::round(pos / static_cast<float>(SECTOR_SIZE));
}

