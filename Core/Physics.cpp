#include "Physics.h"



Physics::Physics(glm::mat4 &model)
  : mModel(model)
{
}


Physics::~Physics()
{
}

void Physics::Forse(const glm::vec3 &forse)
{
  mModel[3][0] += forse[0];
  mModel[3][1] += forse[1];
  mModel[3][2] += forse[2];
}

void Physics::Update()
{

}
