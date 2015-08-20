#include "BlockSimple.h"



BlockSimple::BlockSimple()
{
}


BlockSimple::~BlockSimple()
{
}

void BlockSimple::SetModel(Model *model)
{
  mModel.reset(model);
}

bool BlockSimple::IsStatic() const
{
  return true;
}
