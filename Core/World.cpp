#include "World.h"
#include "..\Graphic\RegistryGraphic.h"


World::World()
{
}


World::~World()
{
}

void World::LoadSector(const glm::ivec3 &pos)
{
  // ���������, �������� �� ������.

  const auto sector = mMap.find(pos);
  if (sector == mMap.end())
  {
    // �� ����� ������, �������� ���.
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
    else
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
