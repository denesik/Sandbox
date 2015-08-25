#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <memory>
#include <glm/gtc/quaternion.hpp>

class Camera;
typedef std::shared_ptr<Camera> PCamera;

class Camera
{
public:
  Camera();
  ~Camera();

  /// Получить матрицу вида.
  const glm::mat4 &GetView() const;

  /// Получить матрицу проекции.
  const glm::mat4 &GetProject() const;

  const glm::mat3 &GetDirection() const;

  void SetPos(const glm::vec3 &pos);

  void Resize(const glm::uvec2 &size);

  void Rotate(const glm::vec3 &angle);

  void Move(const glm::vec3 &dist);

  void Update();

private:

  glm::mat4 mView;
  glm::mat4 mProjection;
  glm::mat3 mDirection;

  float mFov;
  float mAspect;
  float mNear;
  float mFar;

  glm::vec3 mDir;
  glm::vec3 mPos;
  glm::quat mQuat;
};