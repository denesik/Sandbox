#pragma once

#include <glm/glm.hpp>
#include <vector>

struct VertexVT
{
  glm::vec3 vertex;
  glm::vec2 texture;
};

class Cube
{
public:
  Cube();
  ~Cube();

  std::vector<VertexVT> mVertex;
  std::vector<unsigned int> mIndex;
};

