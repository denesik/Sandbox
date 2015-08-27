// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Model_h__
#define Model_h__

#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include "BufferArray.h"

struct VertexVT
{
  VertexVT() {};
  VertexVT(const glm::vec3 &v, const glm::vec2 &t)
    : vertex(v), texture(t)
  {};
  glm::vec3 vertex;
  glm::vec2 texture;
};

class Model
{
public:
  enum
  {
    EMPTY = 0,

    FRONT = 1 << 0,
    RIGHT = 1 << 1,
    BACK = 1 << 2,
    LEFT = 1 << 3,
    TOP = 1 << 4,
    BOTTOM = 1 << 5,

    ALL = 0x3F,
  };
  typedef unsigned int Side;

public:
  Model();
  virtual ~Model();

  virtual const PTexture &GetTexture() const;

  virtual void FillBuffer(BufferArray<VertexVT> &buffer, const glm::vec3 &pos) const = 0;

  virtual void FillBuffer(BufferArray<VertexVT> &buffer, const glm::vec3 &pos, Side sides) const = 0;

protected:

  PTexture mTexture;

  std::vector<VertexVT> mVertex;
  std::vector<unsigned int> mIndex;

};



#endif // Model_h__
