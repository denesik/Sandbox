#include "Sector.h"

#include <memory>
#include "..\RegistryCore.h"



Sector::Sector()
{
  for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
    for (unsigned int x = 0; x < SECTOR_SIZE; ++x)
    {
      mMap[z][0][x] = x % 2 ? REGISTRY_CORE.GetBlocksLibrary().Create("block1") : 
        REGISTRY_CORE.GetBlocksLibrary().Create("block2");
    }
}


Sector::~Sector()
{
}

