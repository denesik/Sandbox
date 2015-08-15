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
  mProjection = glm::perspective(mFov, mAspect, mNear, mFar);
}


Camera::~Camera(void)
{
}

const glm::mat4 &Camera::GetView() const
{
  return mView;
}

const glm::mat4 &Camera::GetProject() const
{
  return mProjection;
}

void Camera::Resize(const glm::uvec2 &size)
{
  mAspect = static_cast<float>(size.x) / static_cast<float>(size.y);
  mProjection = glm::perspective(mFov, mAspect, mNear, mFar);
}

void Camera::SetFov(float fov)
{
  mFov = fov;
}

void Camera::SetFar(float far)
{
  mFar = far;
}

void Camera::SetNear(float near)
{
  mNear = near;
}

void Camera::RotateX(float angle)
{
  mRot.x += angle;
}

void Camera::RotateY(float angle)
{
  mRot.y += angle;
}

void Camera::Move(const glm::vec3 &dist)
{
  mPos -= dist;
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
