#include "Game.h"

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
#include "RegistryCore.h"


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

  glfwSwapInterval(0);
  glfwWindowHint(GLFW_SAMPLES, 16);
  RenderCheckErrors();

  glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
  glDepthFunc(GL_LEQUAL);            // Тип теста глубины

  glClearColor(117.0f / 255.0f, 187.0f / 255.0f, 253.0f / 255.0f, 1.0f);

  RenderCheckErrors();
  glViewport(0, 0, REGISTRY_GRAPHIC.GetWindow().GetSize().x, REGISTRY_GRAPHIC.GetWindow().GetSize().y); 
}

Game::~Game()
{

}


int Game::Run()
{
  if (!Initialized)
  {
    system("pause");
    return -1;
  }

  {
    REGISTRY_GRAPHIC.GetCamera().Resize(REGISTRY_GRAPHIC.GetWindow().GetSize());

    Shader shader("Graphic/Shaders/t");

    REGISTRY_GRAPHIC.GetTextureManager().LoadTexture({ "Textures/stone.png", "Textures/sand.png" });
    REGISTRY_GRAPHIC.GetTextureManager().Compile();
    std::get<0>(REGISTRY_GRAPHIC.GetTextureManager().GetTexture("Textures/stone.png"))->Set(TEXTURE_SLOT_0);

    RenderCheckErrors();

    BlockSimple *block1 = new BlockSimple;
    Cube *cube1 = new Cube;
    cube1->SetTexture(Cube::ALL, "Textures/stone.png");
    block1->SetModel(cube1);
    REGISTRY_CORE.GetBlocksLibrary().Registry("block1", block1);

    BlockSimple *block2 = new BlockSimple;
    Cube *cube2 = new Cube;
    cube2->SetTexture(Cube::ALL, "Textures/sand.png");
    block2->SetModel(cube2);
    REGISTRY_CORE.GetBlocksLibrary().Registry("block2", block2);

    
    auto currentTime = glfwGetTime();
    Sector sector;
    RenderSector renderSector(sector);
    renderSector.Generate();
    std::cout << "GenAll: " << glfwGetTime() - currentTime << std::endl;

    RenderCheckErrors();

    const unsigned int TICKS_PER_SECOND = 50;
    const unsigned int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const unsigned int MAX_FRAMESKIP = 10;

    double tick = glfwGetTime();

    FpsCounter fps;
    while (!REGISTRY_GRAPHIC.GetWindow().WindowShouldClose())
    {
      fps.Update();
      REGISTRY_GRAPHIC.GetWindow().SetTitle(std::to_string(fps.GetCount()) + " fps");

      for (int loops = 0; glfwGetTime() > tick && loops < MAX_FRAMESKIP; ++loops)
      {
        Update();
        tick += SKIP_TICKS / 1000.0;
      }

      glm::mat4 model; 
      glm::mat4 MVP = REGISTRY_GRAPHIC.GetCamera().GetProject() * REGISTRY_GRAPHIC.GetCamera().GetView() * model;

      shader.Use();
      shader.SetUniform(MVP);
      int colorTexture = TEXTURE_SLOT_0;
      shader.SetUniform(colorTexture);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Очистка экрана

      //renderSector.Generate();
      renderSector.GetBuffer().Draw();

      RenderCheckErrors();

      REGISTRY_GRAPHIC.GetWindow().SwapBuffers();
      Window::WindowSystemPollEvents();
    }
  }

  return 0;
}

void Game::Update()
{
  const float speed = 0.2f;

  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_A))
  {
    REGISTRY_GRAPHIC.GetCamera().Move({ speed, 0.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_D))
  {
    REGISTRY_GRAPHIC.GetCamera().Move({ -speed, 0.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_W))
  {
    REGISTRY_GRAPHIC.GetCamera().Move({ 0.0f, 0.0f, speed });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_S))
  {
    REGISTRY_GRAPHIC.GetCamera().Move({ 0.0f, 0.0f, -speed });
  }

  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_LEFT))
  {
    REGISTRY_GRAPHIC.GetCamera().Rotate({ 0.0f, -speed / 4.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_RIGHT))
  {
    REGISTRY_GRAPHIC.GetCamera().Rotate({ 0.0f, speed / 4.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_DOWN))
  {
    REGISTRY_GRAPHIC.GetCamera().Rotate({ speed / 4.0f, 0.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_UP))
  {
    REGISTRY_GRAPHIC.GetCamera().Rotate({ -speed / 4.0f, 0.0f, 0.0f });
  }
  float ay = REGISTRY_GRAPHIC.GetWindow().GetMouse().IsMoveX() / 30.0f;
  float ax = REGISTRY_GRAPHIC.GetWindow().GetMouse().IsMoveY() / 30.0f;
  REGISTRY_GRAPHIC.GetCamera().Rotate(glm::vec3(ax, ay, 0.0f) / 2.0f);

  REGISTRY_GRAPHIC.GetWindow().GetMouse().Update();
  REGISTRY_GRAPHIC.GetCamera().Update();
}

void Game::Draw()
{

}
