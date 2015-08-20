#pragma once

#include <string>
#include "Model.h"



class Cube : public Model
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

  void SetTexture(Side side, const std::string &name);

  void FillBuffer(BufferArray<VertexVT> &buffer, const glm::vec3 &pos) const override;
};

