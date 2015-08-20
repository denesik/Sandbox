#pragma once

#include "Graphic\Render\Cube.h"
#include "Graphic\Render\BufferArray.h"
#include "core\Sector.h"




class RenderSector
{
public:
  RenderSector(const Sector &sector);
  ~RenderSector();

  void Generate();

  BufferArray<VertexVT> &GetBuffer();

private:

  const Sector &mSector;

  BufferArray<VertexVT> mBufferStatic;

};

