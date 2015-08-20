#include "BlocksLibrary.h"



BlocksLibrary::BlocksLibrary()
{
}


BlocksLibrary::~BlocksLibrary()
{
  for (auto &i : mBlocks)
  {
    delete i.second;
  }
}

void BlocksLibrary::Registry(const std::string &id, IBlock *block)
{
  mBlocks[id] = block;
}

IBlock * BlocksLibrary::Create(const std::string &id)
{
  IBlock *block = mBlocks[id];
  return block->IsStatic() ? block : block->Clone();
}
