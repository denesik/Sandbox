// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Sector.h"

#include <memory>
#include "..\RegistryCore.h"


#include <GLFW\glfw3.h>
#include <iostream>
#include "MapGen\PerlinNoise.h"

static PerlinNoise noise(0);

Sector::Sector(const glm::ivec3 &pos)
  : mPos(pos), mRenderSector(*this, pos)
{
  auto currentTime = glfwGetTime();
  for (unsigned int y = 0; y < SECTOR_SIZE; ++y)
  for (unsigned int x = 0; x < SECTOR_SIZE; ++x)
  {
//     for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
//     {
//       if (z == 0)
//       {
//         mMap[z][y][x] = x % 2 ? REGISTRY_CORE.GetBlocksLibrary().Create("block1") :
//           REGISTRY_CORE.GetBlocksLibrary().Create("block2");
//       }
//       else
//       {
//         mMap[z][y][x] = nullptr;
//       }
//     }
    float tx = mPos.x * SECTOR_SIZE + static_cast<int>(x);
    float ty = mPos.y * SECTOR_SIZE + static_cast<int>(y);
    float h = (noise.Noise2(tx / 10.0f, ty / 10.0f) + 1.0f) / 2.0f;
    unsigned int zh = glm::round(h * (SECTOR_SIZE - 1));
    for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
    {
      if (z <= zh)
      {
        mMap[z][y][x] = x % 2 ? REGISTRY_CORE.GetBlocksLibrary().Create("block1") :
                                REGISTRY_CORE.GetBlocksLibrary().Create("block2");
      }
      else
      {
        mMap[z][y][x] = nullptr;
      }
    }
  }

//   mMap[0][0][0] = REGISTRY_CORE.GetBlocksLibrary().Create("block1");
//   mMap[1][0][0] = REGISTRY_CORE.GetBlocksLibrary().Create("block1");
//   mMap[2][0][0] = REGISTRY_CORE.GetBlocksLibrary().Create("block1");
//   mMap[3][0][0] = REGISTRY_CORE.GetBlocksLibrary().Create("block1");
//   mMap[4][0][0] = REGISTRY_CORE.GetBlocksLibrary().Create("block1");
// 
//   mMap[0][0][1] = REGISTRY_CORE.GetBlocksLibrary().Create("block2");
//   mMap[0][0][2] = REGISTRY_CORE.GetBlocksLibrary().Create("block2");
//   mMap[0][0][3] = REGISTRY_CORE.GetBlocksLibrary().Create("block2");

  std::cout << "SectorGen: " << glfwGetTime() - currentTime << std::endl;
  mRenderSector.Changed();
}


Sector::~Sector()
{
}

const glm::ivec3 & Sector::GetPos() const
{
  return mPos;
}

const IBlock * Sector::GetBlock(const glm::uvec3 &pos) const
{
  return mMap[pos.z][pos.y][pos.x];
}

RenderSector & Sector::GetRenderSector()
{
  return mRenderSector;
}

