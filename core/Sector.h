#pragma once

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

  /// ¬ернуть позицию сектора.
  const glm::ivec3 &GetPos() const;

  /// ¬ернуть позицию сектора в системе координат сектора.
  const IBlock *GetBlock(const glm::uvec3 &pos) const;

private:
  IBlock *mMap[SECTOR_SIZE][SECTOR_SIZE][SECTOR_SIZE];

  glm::ivec3 mPos;

private:
  Sector(const Sector &) = delete;
  Sector& operator=(const Sector &) = delete;
};

