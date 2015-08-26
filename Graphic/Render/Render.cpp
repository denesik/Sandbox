#include "Render.h"

#include "RenderErrorChecker.h"
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../RegistryGraphic.h"

Render::Render(void)
{
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
  glDepthFunc(GL_LEQUAL);            // Тип теста глубины

  glClearColor(117.0f / 255.0f, 187.0f / 255.0f, 253.0f / 255.0f, 1.0f);

  RenderCheckErrors();

  mShader.reset(new Shader("Graphic/Shaders/t"));
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

void Render::DrawSector(RenderSector &sector)
{
  glm::mat4 MVP = REGISTRY_GRAPHIC.GetCamera().GetProject() * 
                  REGISTRY_GRAPHIC.GetCamera().GetView() * 
                  sector.GetModel();

  mShader->Use();
  mShader->SetUniform(MVP);
  int colorTexture = TEXTURE_SLOT_0;
  mShader->SetUniform(colorTexture);

  sector.GetBuffer().Draw();
}






