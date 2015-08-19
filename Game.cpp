#include "Game.h"

#define GLEW_STATIC
#include <gl/glew.h>
#include "Graphic/Window/Window.h"
#include <iostream>
#include <sstream>
#include "Graphic/Render/TextureManager.h"
#include "Graphic/Render/Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Graphic/RegistryGraphic.h"

#include <fstream>
#include "Graphic/Render/Cube.h"
#include "Graphic/Render/RenderErrorChecker.h"
#include "Graphic/Render/BufferArray.h"
#include "RenderSector.h"
#include "FpsCounter.h"
#include "Graphic/Render/Shader.h"
#include "core/BlockSimple.h"
#include "core/BlocksLibrary.h"
#include <memory>


Game::Game()
{
  try
  {
    REGISTRY_GRAPHIC;
    Initialized = true;
  }
  catch (const char *e)
  {
    std::cout << e << std::endl;
    return;
  }
}

Game::~Game()
{

}


template< typename T >
std::string ToString(const T& val)
{
  std::stringstream iss;
  iss << val;
  return iss.str();
}

int Game::Run()
{
  if (!Initialized)
  {
    system("pause");
    return -1;
  }

  {

    RenderCheckErrors();

    double tps = 10.0;

    PCamera cam = std::make_shared<Camera>();

    glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
    glDepthFunc(GL_LEQUAL);            // Тип теста глубины

    RenderCheckErrors();

    glViewport(0, 0, REGISTRY_GRAPHIC.GetWindow().GetSize().x, REGISTRY_GRAPHIC.GetWindow().GetSize().y);          // Сброс текущей области вывода
    cam->Resize(REGISTRY_GRAPHIC.GetWindow().GetSize());

    RenderCheckErrors();

    Shader shader("Graphic/Shaders/t");

    RenderCheckErrors();


    REGISTRY_GRAPHIC.GetTextureManager().LoadTexture("Graphic/Textures/tmp2.png");
    REGISTRY_GRAPHIC.GetTextureManager().LoadTexture("Graphic/Textures/tmp.png");
    REGISTRY_GRAPHIC.GetTextureManager().Compile();
    std::get<0>(REGISTRY_GRAPHIC.GetTextureManager().GetTexture("Graphic/Textures/tmp2.png"))->Set(TEXTURE_SLOT_0);

    RenderCheckErrors();

    RenderSector sector;
    sector.Generate();
    sector.mBufferStatic.Compile();

    RenderCheckErrors();

    FpsCounter fps;

    while (!REGISTRY_GRAPHIC.GetWindow().WindowShouldClose())
    {
      fps.Update();
      REGISTRY_GRAPHIC.GetWindow().SetTitle(ToString(fps.GetCount()) + " fps");

      if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_A))
      {
        cam->Move({ -0.01f, 0.0f, 0.0f });
      }
      if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_D))
      {
        cam->Move({ 0.01f, 0.0f, 0.0f });
      }
      if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_W))
      {
        cam->Move({ 0.0f, 0.0f, 0.01f });
      }
      if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_S))
      {
        cam->Move({ 0.0f, 0.0f, -0.01f });
      }

      if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_LEFT))
      {
        cam->RotateY(0.005f);
      }
      if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_RIGHT))
      {
        cam->RotateY(-0.005f);
      }
      if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_DOWN))
      {
        cam->RotateX(0.005f);
      }
      if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_UP))
      {
        cam->RotateX(-0.005f);
      }
      float ay = REGISTRY_GRAPHIC.GetWindow().GetMouse().IsMoveX() / 30.0f;
      float ax = REGISTRY_GRAPHIC.GetWindow().GetMouse().IsMoveY() / 30.0f;

      //cam->RotateX(ax);
      //cam->RotateY(-ay);

      cam->Update();

      glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -6.0f));
      glm::mat4 MVP = cam->GetProject() * cam->GetView() * model;

      shader.Use();
      shader.SetUniform(MVP);
      int colorTexture = TEXTURE_SLOT_0;
      shader.SetUniform(colorTexture);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Очистка экрана
      //sector.Generate();
      //sector.mBufferStatic.Compile();
      sector.mBufferStatic.Draw();

      RenderCheckErrors();

      REGISTRY_GRAPHIC.GetWindow().SwapBuffers();
      REGISTRY_GRAPHIC.GetWindow().GetMouse().Update();
      Window::WindowSystemPollEvents();
    }
  }

  return 0;
}
