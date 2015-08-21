#include "Camera.h"


#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(void)
  : mView(glm::lookAt
    (
      glm::vec3(-1.0f, 0.0f, 0.0f), // eye
      glm::vec3(0.0f, 0.0f, 0.0f), // center
      glm::vec3(0.0f, 0.0f, 1.0f)  // up
    ))
{
  camera_look_at = glm::vec3(0.0f, 0.0f, 0.0f);
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


void Camera::RotateX(float degrees)
{
  camera_pitch -= degrees;

  //Check bounds for the camera pitch
  if (camera_pitch > 360.0f) {
    camera_pitch -= 360.0f;
  }
  else if (camera_pitch < -360.0f) {
    camera_pitch += 360.0f;
  }
}

void Camera::RotateY(float degrees)
{
  camera_heading += degrees;

  //Check bounds for the camera heading
  if (camera_heading > 360.0f) {
    camera_heading -= 360.0f;
  }
  else if (camera_heading < -360.0f) {
    camera_heading += 360.0f;
  }
}

void Camera::Move(const glm::vec3 &dist)
{
  camera_position_delta += camera_direction * dist.z + 
    glm::cross(camera_direction, glm::vec3(0, 0, 1)) * dist.x;
}

void Camera::Update()
{
  camera_direction = glm::normalize(camera_look_at - camera_position);


  //detmine axis for pitch rotation
  glm::vec3 axis = glm::cross(camera_direction, glm::vec3(0, 0, 1));
  //compute quaternion for pitch based on the camera pitch angle
  glm::quat pitch_quat = glm::angleAxis(camera_pitch, axis);
  //determine heading quaternion from the camera up vector and the heading angle
  glm::quat heading_quat = glm::angleAxis(camera_heading, glm::vec3(0, 0, 1));
  //add the two quaternions
  glm::quat temp = glm::cross(pitch_quat, heading_quat);
  temp = glm::normalize(temp);
  //update the direction from the quaternion
  camera_direction = glm::rotate(temp, camera_direction);
  //add the camera delta
  camera_position += camera_position_delta;
  //set the look at to be infront of the camera
  camera_look_at = camera_position + camera_direction * 1.0f;

  camera_pitch = 0.0f;
  camera_heading = 0.0f;
  camera_position_delta *= 0.0f;

  //compute the MVP
  mView = glm::lookAt(camera_position, camera_look_at, glm::vec3(0, 0, 1));
  mView = glm::lookAt
    (
      glm::vec3(10.0f, -15.0f, 0.0f), // eye
      glm::vec3(0.0f, 0.0f, 5.0f), // center
      glm::vec3(0.0f, 0.0f, 1.0f)  // up
      );
}

