#include "Block.h"

void Block::SetModel(const std::shared_ptr<Cube>& model)
{
  mModel = model;
}

const Cube &Block::GetModel()
{
  return *mModel.get();
}
