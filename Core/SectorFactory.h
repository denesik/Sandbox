// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef SectorFactory_h__
#define SectorFactory_h__

#include <glm/glm.hpp>
#include <list>
#include "Sector.h"

class SectorFactory
{
public:
  SectorFactory();
  ~SectorFactory();
  SectorFactory(const SectorFactory &) = delete;
  SectorFactory& operator=(const SectorFactory &) = delete;

  /// Создать сектор в заданной позиции.
  void CreateSector(const glm::ivec3 &pos);

  //void DeleteSector(const glm::ivec3 &pos);

  void Update();


private:



};


#endif // SectorFactory_h__


