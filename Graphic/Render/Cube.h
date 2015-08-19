#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include <memory>
#include "Bitmap.h"

struct VertexVT
{
  glm::vec3 vertex;
  glm::vec2 texture;
};

class Cube
{
public:
  enum
  {
    FRONT   = 1 << 0,
    RIGHT   = 1 << 1,
    BACK    = 1 << 2,
    LEFT    = 1 << 3,
    TOP     = 1 << 4,
    BOTTOM  = 1 << 5,

    ALL = 0x3F,
  };
  typedef unsigned int Side;

public:
  Cube();
  ~Cube();

  std::vector<VertexVT> mVertex;
  std::vector<unsigned int> mIndex;

  void SetTexture(Side side, const std::string &name);

  void Compile();

private:

  PTexture mTexture;

};

