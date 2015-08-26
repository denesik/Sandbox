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

  const glm::mat4 &GetModel() const;

private:

  const Sector &mSector;

  BufferArray<VertexVT> mBufferStatic;

private:

  const IBlock *GetBlock(const glm::ivec3 &pos);

  glm::mat4 mModel;

};

