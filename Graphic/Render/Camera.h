#pragma once

#include <glm/glm.hpp>
#include <memory>

class Camera;
typedef std::shared_ptr<Camera> PCamera;

class Camera
{
public:
  Camera();
  ~Camera();

  /// Получить матрицу вида.
  const glm::mat4 &GetView();

  /// Получить матрицу проекции.
  const glm::mat4 &GetProject();

  /// Угол обзора.
  void SetFov(float fov);

  /// Пропорции экрана.
  void SetAspect(float aspect);

  void SetFar(float far);

  void SetNear(float near);

  void RotateX(float angle);
  void RotateY(float angle);

  void MoveX(float dist);
  void MoveY(float dist);
  void MoveZ(float dist);

  void Update();

private:

  glm::mat4 mView;
  glm::mat4 mProjection;

  glm::mat4 mViewCurr;
  glm::mat4 mViewRotateY;

  float mFov;
  float mAspect;
  float mNear;
  float mFar;

  glm::mat4 mPosMat;
  glm::mat4 mRotMat;

  glm::vec3 mPos;
  glm::vec3 mRot;

public:

  void UpdateProjection();

};