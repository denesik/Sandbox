#include "Render.h"

#include "RenderErrorChecker.h"
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Render::Render(void)
{
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  RenderCheckErrors();

//  glEnable(GL_TEXTURE_2D); // Включаем текстурирование.

//   glEnable(GL_BLEND);
//   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//   glClearDepth(GL_TRUE);              // Разрешить очистку буфера глубины
//   glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
//   glDepthFunc(GL_LEQUAL);             // Тип теста глубины

  RenderCheckErrors();
}

Render::~Render(void)
{
}

void Render::Initialize()
{
  glewExperimental = true; // Needed in core profile

  GLenum error = glewInit();
  if(error != GLEW_OK)
  {
    std::cout << "glew error: " << glewGetErrorString(error) << std::endl;
    throw "GLEW not initialized.";
  }
  glGetError();
}

void Render::UseCam(const PCamera &camera)
{
  mCamera = camera;
}





