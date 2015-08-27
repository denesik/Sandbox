// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef BlocksLibrary_h__
#define BlocksLibrary_h__

#include <unordered_map>
#include <string>
#include "Block.h"

class BlocksLibrary
{
public:
  BlocksLibrary();
  ~BlocksLibrary();

  /// Зарегистрировать блок.
  void Registry(const std::string &id, IBlock *block);

  /// Создать блок.
  /// Если блок статический, возвращается указатель на экземпляр блока, хранящийся в библиотеке.
  /// Если блок динамический, создается копия блока.
  /// @param blockId Идентификатор блока.
  IBlock *Create(const std::string &id);

private:

  std::unordered_map<std::string, IBlock *> mBlocks;
};


#endif // BlocksLibrary_h__


