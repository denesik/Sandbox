#include "Model.h"



Model::Model()
{
}


Model::~Model()
{
}

const std::vector<VertexVT> & Model::GetVertex() const
{
  return mVertex;
}

const std::vector<unsigned int> & Model::GetIndex() const
{
  return mIndex;
}

const PTexture & Model::GetTexture() const
{
  return mTexture;
}
