#pragma once
#ifndef BlocksLibrary_h__
#define BlocksLibrary_h__

#include <unordered_map>
#include "Block.h"

class BlocksLibrary
{
public:
  BlocksLibrary();
  ~BlocksLibrary();

  unsigned int Registry(const BlockBase *block);

  BlockBase *Create(unsigned int blockId);

private:

  std::unordered_map<unsigned int, const BlockBase *> mBlocks;

};


#endif // BlocksLibrary_h__


