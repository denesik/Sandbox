// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef RegistryCore_h__
#define RegistryCore_h__

#include "core\BlocksLibrary.h"
#include "Core\Creature.h"
#include "Core\World.h"
#include "Core\Player.h"

#define REGISTRY_CORE RegistryCore::Instatce()

class RegistryCore
{
public:
  static RegistryCore &Instatce();

  BlocksLibrary &GetBlocksLibrary();

  World &GetWorld();

  Player &GetPlayer();

private:
  RegistryCore();
  ~RegistryCore();
  RegistryCore(const RegistryCore &);
  RegistryCore& operator=(const RegistryCore &);

private:

  BlocksLibrary mBlocksLibrary;
  World mWorld;
  Player mPlayer;

};

#endif // RegistryCore_h__
