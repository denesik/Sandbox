#pragma once
#ifndef Physics_h__
#define Physics_h__

#include <glm/glm.hpp>

class Physics
{
public:
  Physics(glm::mat4 &model);
  ~Physics();

  void Forse(const glm::vec3 &forse);

  void Update();

private:
  glm::mat4 &mModel;

};



#endif // Physics_h__

