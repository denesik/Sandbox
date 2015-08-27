// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
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
