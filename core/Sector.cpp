#include "Sector.h"

#include <memory>
#include "..\RegistryCore.h"



Sector::Sector()
{
  for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
  for (unsigned int y = 0; y < SECTOR_SIZE; ++y)
  for (unsigned int x = 0; x < SECTOR_SIZE; ++x)
  {
    if (y == 0)
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


Sector::~Sector()
{
}

