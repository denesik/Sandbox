// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RenderSector_h__
#define RenderSector_h__

#include "Cube.h"
#include "BufferArray.h"
#include "..\..\core\Block.h"
class Sector;

class RenderSector
{
public:
  RenderSector(Sector &sector, const glm::ivec3 &pos);
  ~RenderSector();

  const glm::mat4 &GetModel() const;

  void Draw();

private:

  Sector &mSector;

  BufferArray<VertexVT> mBufferStatic;

private:

  void Generate();

  const IBlock *GetBlock(const glm::ivec3 &pos);

  glm::mat4 mModel;

};



#endif // RenderSector_h__

