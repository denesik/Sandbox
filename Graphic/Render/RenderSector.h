// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RenderSector_h__
#define RenderSector_h__

#include "Cube.h"
#include "BufferArray.h"
#include "..\..\core\Sector.h"

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



#endif // RenderSector_h__

