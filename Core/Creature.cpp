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
  auto dir = static_cast<glm::vec3>(mModel[1]);
  auto dirp = glm::cross(dir, glm::vec3(0, 0, 1));

  Forse(dir * dist.x);
  Forse(dirp * dist.y);
}

