// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef SectorLoader_h__
#define SectorLoader_h__

#include <glm/glm.hpp>
#include <vector>
#include "World.h"

class SectorLoader
{
public:
  SectorLoader(World &world);
  ~SectorLoader();

  void SetRadius(unsigned int radius);

  void SetPos(const glm::ivec3 &pos);

private:

  World &mWorld;

  unsigned int mRadius = 0;

  glm::ivec3 mPos;

  std::vector<glm::ivec3> mSite;

private:
  SectorLoader(const SectorLoader &) = delete;
  SectorLoader& operator=(const SectorLoader &) = delete;
};



#endif // SectorLoader_h__

