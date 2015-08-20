#pragma once

#include <string>
#include "Model.h"



class Cube : public Model
{
public:
  Cube();
  ~Cube();

  void SetTexture(Side side, const std::string &name);

  void FillBuffer(BufferArray<VertexVT> &buffer, const glm::vec3 &pos) const override;

  void FillBuffer(BufferArray<VertexVT> &buffer, const glm::vec3 &pos, Side sides) const override;

private:

  inline void FillBufferSide(BufferArray<VertexVT> &buffer, const glm::vec3 &pos, unsigned int side) const;

};

