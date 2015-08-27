// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "SectorLoader.h"
#include "World.h"


SectorLoader::SectorLoader(World &world, const glm::ivec3 &pos, unsigned int radius)
  : mWorld(world), mPos(pos)
{
  SetRadius(radius);
  SetPos(pos);
}

SectorLoader::~SectorLoader()
{
}

void SectorLoader::SetRadius(unsigned int radius)
{
  mRadius = radius;

  mSite.clear();

  int begin = -static_cast<int>(radius);
  int end = static_cast<int>(radius);
  glm::ivec3 pos(begin); pos.z = -2;
//  for (pos.z = 0; pos.z != end; ++pos.z)
  for (pos.y = 0; pos.y != end; ++pos.y)
  for (pos.x = 0; pos.x != end; ++pos.x)
  {
    mSite.push_back(pos);
  }

}

void SectorLoader::SetPos(const glm::ivec3 &pos)
{
  if (mPos == pos)
  {
    return;
  }

  // Пробегаем по всем загруженным на данный момент секторам и выгружаем их.
  for (const auto &site : mSite)
  {
    mWorld.UnloadSector(mPos + site);
  }

  mPos = pos;
  mPos.z = 0;
  // Загружаем нужные сектора.
  for (const auto &site : mSite)
  {
    mWorld.LoadSector(mPos + site);
  }
}
