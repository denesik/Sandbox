﻿// ============================================================================
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
  RenderSector(const Sector &sector, const glm::ivec3 &pos);
  ~RenderSector();

  const glm::mat4 &GetModel() const;

  /// Нарисовать сектор.
  void Draw();

  /// Необходимо вызывать, если сектор изменился.
  void Changed();

private:

  const Sector &mSector;

  BufferArray<VertexVT> mBufferStatic;

  glm::mat4 mModel;

  bool mChanged = false;

private:

  void Generate();

  const IBlock *GetBlock(const glm::ivec3 &pos);
};



#endif // RenderSector_h__

