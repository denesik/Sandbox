#pragma once

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

  void Resize(const glm::uvec2 &size);

  // (up, down)
  void RotateX(float angle);

  // (left, right)
  void RotateY(float angle);

  void Move(const glm::vec3 &dist);

  void Update();

private:

  glm::mat4 mView;
  glm::mat4 mProjection;

  float mFov;
  float mAspect;
  float mNear;
  float mFar;

  glm::quat mQuat;
  float camera_pitch = 0.0f;
  float camera_heading = 0.0f;
  glm::vec3 camera_position;
  glm::vec3 camera_position_delta;
  glm::vec3 camera_look_at;
  glm::vec3 camera_direction;
};