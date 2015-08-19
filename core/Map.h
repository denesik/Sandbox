#pragma once


enum
{
  SECTOR_SIZE = 32,
};

class Map
{
public:
  Map();
  ~Map();

  char mMap[SECTOR_SIZE][SECTOR_SIZE][SECTOR_SIZE];

};

