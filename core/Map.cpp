#include "Map.h"

#include <memory>



Map::Map()
{
  memset(mMap, 0, SECTOR_SIZE * SECTOR_SIZE * SECTOR_SIZE);
  for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
    for (unsigned int x = 0; x < SECTOR_SIZE; ++x)
    {
      mMap[z][0][x] = x % 2 ? 1 : 2;
    }
}


Map::~Map()
{
}

