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

Creature & RegistryCore::GetPlayer()
{
  return mPlayer;
}

World &RegistryCore::GetWorld()
{
  return mWorld;
}

RegistryCore::RegistryCore()
{

}

RegistryCore::~RegistryCore()
{
}


