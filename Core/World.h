﻿// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef World_h__
#define World_h__

#include <unordered_map>
#include <glm/glm.hpp>
#include "Sector.h"
#include "../Graphic/Render/RenderSector.h"

namespace std
{
  template <>
  struct hash<glm::ivec3>
  {
    std::size_t operator()(glm::ivec3 const& v) const
    {
      std::size_t h1 = std::hash<int>()(v.x);
      std::size_t h2 = std::hash<int>()(v.y);
      std::size_t h3 = std::hash<int>()(v.z);
      return ((h1 ^ (h2 << 1)) >> 1) ^ (h3 << 1);
    }
  };
}


class World
{
public:
  World();
  ~World();

  void LoadSector(const glm::ivec3 &pos);

  void UnloadSector(const glm::ivec3 &pos);

  void Update();

  void Draw();

private:

  struct WorldSector
  {
    WorldSector(const glm::ivec3 &pos)
      : sector(pos), renderSector(sector)
    {
      renderSector.Generate();
    };
    Sector sector;
    RenderSector renderSector;
    unsigned int refCount = 1;

  private:
    WorldSector(const WorldSector &) = delete;
    WorldSector& operator=(const WorldSector &) = delete;
  };

  std::unordered_map<glm::ivec3, WorldSector> mMap;

private:
  World(const World &) = delete;
  World& operator=(const World &) = delete;

};



#endif // World_h__

