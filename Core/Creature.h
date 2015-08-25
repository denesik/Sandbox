#pragma once
#ifndef Creature_h__
#define Creature_h__

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Physics.h"

/// Существо. Может перемещаться и вращаться.
class Creature : public Physics
{
public:
  Creature();
  virtual ~Creature();

  void SetDirection(const glm::mat3 &directon);

  void SetPosition(const glm::vec3 &position);

  glm::vec3 GetPosition() const;

  void Move(const glm::vec3 &dist);

protected:
  glm::mat4 mModel;

};



#endif // Creature_h__
