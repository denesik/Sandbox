#pragma once

#include "Graphic\Render\Cube.h"
#include "Graphic\Render\BufferArray.h"


enum 
{
  SECTOR_SIZE = 32,
};


class RenderSector
{
public:
  RenderSector();
  ~RenderSector();

  void Generate();

  char mMap[SECTOR_SIZE][SECTOR_SIZE][SECTOR_SIZE];


public:

  BufferArray<VertexVT> mBufferStatic;

};

