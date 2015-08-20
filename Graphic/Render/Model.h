#pragma once

#ifndef Model_h__
#define Model_h__

#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"

struct VertexVT
{
  glm::vec3 vertex;
  glm::vec2 texture;
};

class Model
{
public:
  Model();
  virtual ~Model();

  virtual const std::vector<VertexVT> &GetVertex() const;

  virtual const std::vector<unsigned int> &GetIndex() const;

  virtual const PTexture &GetTexture() const;

protected:

  PTexture mTexture;

  std::vector<VertexVT> mVertex;
  std::vector<unsigned int> mIndex;

};



#endif // Model_h__
