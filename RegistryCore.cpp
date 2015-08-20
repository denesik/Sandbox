#include "RegistryCore.h"

RegistryCore &RegistryCore::Instatce()
{
  static RegistryCore registry;
  return registry;
}

BlocksLibrary & RegistryCore::GetBlocksLibrary()
{
  return mBlocksLibrary;
}

RegistryCore::RegistryCore()
{

}

RegistryCore::~RegistryCore()
{
}


