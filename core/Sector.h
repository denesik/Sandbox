// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Sector_h__
#define Sector_h__


#include "Block.h"


enum
{
  SECTOR_SIZE = 16,
};

class Sector
{
public:
  Sector(const glm::ivec3 &pos);
  ~Sector();

  /// Вернуть позицию сектора.
  const glm::ivec3 &GetPos() const;

  /// Вернуть позицию сектора в системе координат сектора.
  const IBlock *GetBlock(const glm::uvec3 &pos) const;

private:
  IBlock *mMap[SECTOR_SIZE][SECTOR_SIZE][SECTOR_SIZE];

  glm::ivec3 mPos;

private:
  Sector(const Sector &) = delete;
  Sector& operator=(const Sector &) = delete;
};


#endif // Sector_h__

