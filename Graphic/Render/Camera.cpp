#include "Camera.h"


#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(void)
  : mViewCurr(glm::lookAt
  (
  glm::vec3(0.0f, 0.0f,  1.0f), // eye
  glm::vec3(0.0f, 0.0f,  0.0f), // center
  glm::vec3(0.0f, 1.0f,  0.0f)  // up
  )), mViewRotateY(1.0f)
{
  mFov = 45.0f;
  mAspect = 1.0f;
  mNear = 1.0f;
  mFar = 100.0f;
}


Camera::~Camera(void)
{
}

const glm::mat4 &Camera::GetView()
{
  return mView;
}

const glm::mat4 &Camera::GetProject()
{
  return mProjection;
}

void Camera::SetFov(float fov)
{
  mFov = fov;
}

void Camera::SetAspect(float aspect)
{
  mAspect = aspect;
}

void Camera::SetFar(float far)
{
  mFar = far;
}

void Camera::SetNear(float near)
{
  mNear = near;
}

void Camera::UpdateProjection()
{
  mProjection = glm::perspective(mFov, mAspect, mNear, mFar);
}

void Camera::RotateX(float angle)
{
  mRot.x += angle;
}

void Camera::RotateY(float angle)
{
  mRot.y += angle;
}

void Camera::MoveX(float dist)
{
  mPos.x -= dist;
}

void Camera::MoveY(float dist)
{
  mPos.y -= dist;
}

void Camera::MoveZ(float dist)
{
  mPos.z -= dist;
}

void Camera::Update()
{
  // ¬ычисл€ем поворот относительно локальной системы координат.
  // ¬ычисл€ем перенов относительно поворота.
  // ¬ычисл€ем мировую матрицу вида.
  auto rot = glm::rotate(glm::mat4(), mRot.y, glm::vec3(0.0f, 1.0f, 0.0f));
  mView = glm::translate(glm::mat4(), mPos) * glm::rotate(mView, mRot.y, glm::vec3(0.0f, 1.0f, 0.0f));
  mRot = mPos = glm::vec3();
}
