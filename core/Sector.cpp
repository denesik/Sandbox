#include "Sector.h"

#include <memory>
#include "..\RegistryCore.h"


#include <GLFW\glfw3.h>
#include <iostream>



Sector::Sector()
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

  std::cout << "MapGen: " << glfwGetTime() - currentTime << std::endl;
}


Sector::~Sector()
{
}

