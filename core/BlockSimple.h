#pragma once
#ifndef BlockSimple_h__
#define BlockSimple_h__

#include "Block.h"

class BlockStatic : public Block<BlockStatic>
{
public:
  BlockStatic();
  ~BlockStatic();

  bool IsStatic() const override;

  int test = 0;
};



#endif // BlockSimple_h__
