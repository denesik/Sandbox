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
    }

    if (!sector->second.refCount)
    {
      mMap.erase(sector);
    }
  }
}

void World::Update()
{

}

void World::Draw()
{
  for (auto &sector : mMap)
  {
    REGISTRY_GRAPHIC.GetRender().DrawSector(sector.second.renderSector);
  }
}

