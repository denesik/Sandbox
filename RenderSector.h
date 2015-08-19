#pragma once

#include "Graphic\Render\Cube.h"
#include "Graphic\Render\BufferArray.h"
#include "core\Map.h"




class RenderSector
{
public:
  RenderSector();
  ~RenderSector();

  void Generate();

  Map mMap;

public:

  BufferArray<VertexVT> mBufferStatic;

};

