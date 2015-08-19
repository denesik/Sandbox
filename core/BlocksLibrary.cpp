#include "BlocksLibrary.h"



BlocksLibrary::BlocksLibrary()
{
}


BlocksLibrary::~BlocksLibrary()
{
}

unsigned int BlocksLibrary::Registry(const BlockBase *block)
{

  return 0;
}

BlockBase * BlocksLibrary::Create(unsigned int blockId)
{
  return mBlocks[blockId]->Clone();
}
