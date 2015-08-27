// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef BlockSimple_h__
#define BlockSimple_h__


#include "Block.h"

class BlockSimple : public Block<BlockSimple>
{
public:
  BlockSimple();
  ~BlockSimple();

  void SetModel(Model *model);

  bool IsStatic() const override;
};

#endif // BlockSimple_h__
