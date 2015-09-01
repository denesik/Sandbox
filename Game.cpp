// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
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

  glViewport(0, 0, REGISTRY_GRAPHIC.GetWindow().GetSize().x, REGISTRY_GRAPHIC.GetWindow().GetSize().y); 

  RenderCheckErrors();
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

    glEnable(GL_TEXTURE_2D);

    REGISTRY_CORE.GetWorld().AddPlayer(REGISTRY_CORE.GetPlayer());
    FpsCounter fps;
    FpsCounter tps;

    RenderCheckErrors();

    const unsigned int TICKS_PER_SECOND = 50;
    const unsigned int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const unsigned int MAX_FRAMESKIP = 10;

    double tick = glfwGetTime();
    while (!REGISTRY_GRAPHIC.GetWindow().WindowShouldClose())
    {
      fps.Update();
      REGISTRY_GRAPHIC.GetWindow().SetTitle(std::to_string(fps.GetCount()) + " fps, " + std::to_string(tps.GetCount()) + " tps");

      for (int loops = 0; glfwGetTime() > tick && loops < MAX_FRAMESKIP; ++loops)
      {
        tps.Update();
        Update();
        tick += SKIP_TICKS / 1000.0;
      }

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Очистка экрана

      REGISTRY_CORE.GetWorld().Draw();

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

  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_LEFT))
  {
    REGISTRY_GRAPHIC.GetCamera().Rotate({ 0.0f, 0.0f, -speed / 4.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_RIGHT))
  {
    REGISTRY_GRAPHIC.GetCamera().Rotate({ 0.0f, 0.0f, speed / 4.0f });
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
  //REGISTRY_GRAPHIC.GetCamera().Rotate(glm::vec3(ax, ay, 0.0f) / 2.0f);

  REGISTRY_GRAPHIC.GetCamera().SetPos(REGISTRY_CORE.GetPlayer().GetPosition());

  REGISTRY_GRAPHIC.GetCamera().Update();
  REGISTRY_CORE.GetPlayer().SetDirection(REGISTRY_GRAPHIC.GetCamera().GetDirection());

  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_D))
  {
    REGISTRY_CORE.GetPlayer().Move({ speed, 0.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_A))
  {
    REGISTRY_CORE.GetPlayer().Move({ -speed, 0.0f, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_W))
  {
    REGISTRY_CORE.GetPlayer().Move({ 0.0f, speed, 0.0f });
  }
  if (REGISTRY_GRAPHIC.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_S))
  {
    REGISTRY_CORE.GetPlayer().Move({ 0.0f, -speed, 0.0f });
  }

  REGISTRY_GRAPHIC.GetWindow().GetMouse().Update();

  REGISTRY_CORE.GetWorld().Update();
}

void Game::Draw()
{

}
