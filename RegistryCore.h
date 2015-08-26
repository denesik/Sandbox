#pragma once
#ifndef RegistryCore_h__
#define RegistryCore_h__

#include "core\BlocksLibrary.h"
#include "Core\Creature.h"
#include "Core\World.h"

#define REGISTRY_CORE RegistryCore::Instatce()

class RegistryCore
{
public:
  static RegistryCore &Instatce();

  BlocksLibrary &GetBlocksLibrary();

  Creature &GetPlayer();

  World &GetWorld();

private:
  RegistryCore();
  ~RegistryCore();
  RegistryCore(const RegistryCore &);
  RegistryCore& operator=(const RegistryCore &);

private:

  BlocksLibrary mBlocksLibrary;
  Creature mPlayer;
  World mWorld;

};

#endif // RegistryCore_h__
