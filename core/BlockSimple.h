#pragma once
#ifndef BlockStatic_h__
#define BlockStatic_h__

#include "Block.h"

class BlockSimple : public Block<BlockSimple>
{
public:
  BlockSimple();
  ~BlockSimple();

  void SetModel(Model *model);

  bool IsStatic() const override;
};



#endif // BlockStatic_h__
