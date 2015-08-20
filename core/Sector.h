#pragma once

#include "Block.h"


enum
{
  SECTOR_SIZE = 16,
};

class Sector
{
public:
  Sector();
  ~Sector();

  IBlock *mMap[SECTOR_SIZE][SECTOR_SIZE][SECTOR_SIZE];

};

