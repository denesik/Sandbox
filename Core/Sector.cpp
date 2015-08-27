// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Sector.h"

#include <memory>
#include "..\RegistryCore.h"


#include <GLFW\glfw3.h>
#include <iostream>



Sector::Sector(const glm::ivec3 &pos)
  : mPos(pos)
{
  auto currentTime = glfwGetTime();
  for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
  for (unsigned int y = 0; y < SECTOR_SIZE; ++y)
  for (unsigned int x = 0; x < SECTOR_SIZE; ++x)
  {
    if (true)//(y == 0)
    {
      mMap[z][y][x] = x % 2 ? REGISTRY_CORE.GetBlocksLibrary().Create("block1") :
        REGISTRY_CORE.GetBlocksLibrary().Create("block2");
    }
    else
    {
      mMap[z][y][x] = nullptr;
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

  std::cout << "MapGen: " << glfwGetTime() - currentTime << std::endl;
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

