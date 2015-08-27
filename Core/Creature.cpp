// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Creature.h"

#include <glm/gtc/matrix_transform.hpp>

Creature::Creature()
  : Physics(mModel)
{
}


Creature::~Creature()
{
}

void Creature::SetDirection(const glm::mat3 &directon)
{
  for (unsigned int i = 0; i < 3; ++i)
  for (unsigned int j = 0; j < 3; ++j)
  {
    mModel[i][j] = directon[i][j];
  }
}

void Creature::SetPosition(const glm::vec3 &position)
{
  mModel[3][0] = position[0];
  mModel[3][1] = position[1];
  mModel[3][2] = position[2];
}

glm::vec3 Creature::GetPosition() const
{
  return static_cast<glm::vec3>(mModel[3]);
}

void Creature::Move(const glm::vec3 &dist)
{
  glm::vec3 back(mModel[0][2], mModel[1][2], mModel[2][2]);
  glm::vec3 right(mModel[0][0], mModel[1][0], 0);

  Forse(-back * dist.y);
  Forse(right * dist.x);
}



