#include "BlockSimple.h"



BlockStatic::BlockStatic()
{
  mModel = std::make_shared<Cube>();
}


BlockStatic::~BlockStatic()
{
}

bool BlockStatic::IsStatic() const
{
  return true;
}
