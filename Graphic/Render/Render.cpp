// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Render.h"

#include <GL/glew.h>
#include "RenderErrorChecker.h"
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../RegistryGraphic.h"

Render::Render(void)
{
  glGetIntegerv(GL_MAJOR_VERSION, &mVersion.major);
  glGetIntegerv(GL_MINOR_VERSION, &mVersion.minor);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
  glDepthFunc(GL_LEQUAL);            // Тип теста глубины

  glClearColor(117.0f / 255.0f, 187.0f / 255.0f, 253.0f / 255.0f, 1.0f);

  RenderCheckErrors();

  try
  {
    mShader.reset(new Shader("Graphic/Shaders/t"));
  }
  catch (const char* msg)
  {
    std::cout << msg << std::endl;
  }
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

void Render::DrawSector(RenderSector &renderSector)
{
  if (REGISTRY_GRAPHIC.GetRender().GetVersion().major < 3)
  {
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(REGISTRY_GRAPHIC.GetCamera().GetProject()));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(REGISTRY_GRAPHIC.GetCamera().GetView() * renderSector.GetModel()));
  }
  else
  {
    glm::mat4 MVP = REGISTRY_GRAPHIC.GetCamera().GetProject() *
      REGISTRY_GRAPHIC.GetCamera().GetView() *
      renderSector.GetModel();

    mShader->Use();
    mShader->SetUniform(MVP);
    int colorTexture = TEXTURE_SLOT_0;
    mShader->SetUniform(colorTexture);
  }

  renderSector.Draw();
}

const Render::Version &Render::GetVersion() const
{
  return mVersion;
}





