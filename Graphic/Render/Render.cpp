#include "Render.h"

#include "RenderErrorChecker.h"
#define GLEW_STATIC
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Render::Render(void)
{
//  glEnable(GL_CULL_FACE);
//  glCullFace(GL_BACK);

  RenderCheckErrors();

  glEnable(GL_TEXTURE_2D); // Включаем текстурирование.

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//   glClearDepth(GL_TRUE);              // Разрешить очистку буфера глубины
//   glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
//   glDepthFunc(GL_LEQUAL);             // Тип теста глубины

  RenderCheckErrors();
}


Render::~Render(void)
{
}

void perspective(GLdouble fovY,  GLdouble aspect,  GLdouble zNear,  GLdouble zFar)
{
  const GLdouble PI = 3.1415926535897932384626433832795;

  GLdouble fW, fH;

  fH = tan(fovY / 180.0 * PI) * zNear / 2.0;

  fW = fH * aspect;

  glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

void Render::Initialize()
{
  glewExperimental = true; // Needed in core profile

  GLenum error = glewInit();
  if(error != GLEW_OK)
  {
    printf("glew error: %s\n", glewGetErrorString(error));
    throw new RenderException(RenderException::RENDER_NOT_INITIALIZED);
  }
  glGetError();

  glMatrixMode(GL_MODELVIEW);     // Выбор матрицы вида модели
  glLoadIdentity();               // Сброс матрицы вида модели
}



void Render::UseCam(const PCamera &camera)
{
  mCamera = camera;
}





