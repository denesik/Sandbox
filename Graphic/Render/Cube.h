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
    BACK    = 1 << 1,
    LEFT    = 1 << 2,
    RIGHT   = 1 << 3,
    TOP     = 1 << 4,
    BOTTOM  = 1 << 5,

    t = (RIGHT&-RIGHT),
  };
  typedef unsigned int Side;

public:
  Cube();
  ~Cube();

  std::vector<VertexVT> mVertex;
  std::vector<unsigned int> mIndex;

  PTexture mTexture;

  void SetTexture(Side side, const std::string &name);

  void Compile();

private:

  enum 
  {
    SIDE_SIZE = 32
  };

  std::vector<std::shared_ptr<Bitmap>> mTextures;

};

