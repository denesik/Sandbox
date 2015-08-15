#include "Game.h"

#include <gl/glew.h>
#include "Graphic/Window/Window.h"
#include <iostream>
#include <sstream>
#include "Graphic/Render/TextureManager.h"
#include "Graphic/Render/Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Registry.h"


Game::Game()
{
  try
  {
    REGISTRY;
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

    double tps = 10.0;

    PCamera cam = std::make_shared<Camera>();

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);              // Разрешить очистку буфера глубины
    glEnable(GL_DEPTH_TEST);            // Разрешить тест глубины
    glDepthFunc(GL_LEQUAL);            // Тип теста глубины
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);      // Улучшение в вычислении перспективы

    glViewport(0, 0, REGISTRY.GetWindow().GetSize().x, REGISTRY.GetWindow().GetSize().y);          // Сброс текущей области вывода
    cam->Resize(REGISTRY.GetWindow().GetSize());

    glMatrixMode(GL_PROJECTION);            // Выбор матрицы проекций
    glLoadIdentity();              // Сброс матрицы проекции

                                   // Вычисление соотношения геометрических размеров для окна
    glLoadMatrixf(glm::value_ptr(cam->GetProject()));

    glMatrixMode(GL_MODELVIEW);            // Выбор матрицы вида модели
    glLoadIdentity();              // Сброс матрицы вида модели

    while (!REGISTRY.GetWindow().WindowShouldClose())
    {
      if (REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_A))
      {
        cam->Move({ -0.01f, 0.0f, 0.0f });
      }
      if (REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_D))
      {
        cam->Move({ 0.01f, 0.0f, 0.0f });
      }
      if (REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_W))
      {
        cam->Move({ 0.0f, 0.0f, 0.01f });
      }
      if (REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_S))
      {
        cam->Move({ 0.0f, 0.0f, -0.01f });
      }

      if (REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_LEFT))
      {
        cam->RotateY(0.001f);
      }
      if (REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_RIGHT))
      {
        cam->RotateY(-0.001f);
      }
      if (REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_DOWN))
      {
        cam->RotateX(0.001f);
      }
      if (REGISTRY.GetWindow().GetKeyboard().IsKeyDown(GLFW_KEY_UP))
      {
        cam->RotateX(-0.001f);
      }
      float ay = REGISTRY.GetWindow().GetMouse().IsMoveX() / 30.0f;
      float ax = REGISTRY.GetWindow().GetMouse().IsMoveY() / 30.0f;

      cam->RotateX(ax);
      cam->RotateY(-ay);

      cam->Update();

      //map.Draw();

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Очистка экрана
                                                              // и буфера глубины
      glLoadIdentity();                               // Сброс просмотра

                                                      //glLoadMatrixf(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(-1.5f,0.0f, 0.0f)) * cam->GetView()));
      glLoadMatrixf(glm::value_ptr(cam->GetView()));

      glTranslatef(-1.5f, 0.0f, -6.0f);                 // Сдвиг влево и вглубь экрана
      glBegin(GL_TRIANGLES);                          // Начало рисования пирамиды
      glColor3f(1.0f, 0.0f, 0.0f);                      // Красный
      glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Передняя)
      glColor3f(0.0f, 1.0f, 0.0f);                      // Зеленный
      glVertex3f(-1.0f, -1.0f, 1.0f);                  // Левая точка
      glColor3f(0.0f, 0.0f, 1.0f);                      // Синий
      glVertex3f(1.0f, -1.0f, 1.0f);                  // Правая точка
      glColor3f(1.0f, 0.0f, 0.0f);                      // Красная
      glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Правая)
      glColor3f(0.0f, 0.0f, 1.0f);                      // Синия
      glVertex3f(1.0f, -1.0f, 1.0f);                  // Лево треугольника (Правая)
      glColor3f(0.0f, 1.0f, 0.0f);                      // Зеленная
      glVertex3f(1.0f, -1.0f, -1.0f);                 // Право треугольника (Правая)
      glColor3f(1.0f, 0.0f, 0.0f);                      // Красный
      glVertex3f(0.0f, 1.0f, 0.0f);                  // Низ треугольника (Сзади)
      glColor3f(0.0f, 1.0f, 0.0f);                      // Зеленный
      glVertex3f(1.0f, -1.0f, -1.0f);                 // Лево треугольника (Сзади)
      glColor3f(0.0f, 0.0f, 1.0f);                      // Синий
      glVertex3f(-1.0f, -1.0f, -1.0f);                 // Право треугольника (Сзади)
      glColor3f(1.0f, 0.0f, 0.0f);                      // Красный
      glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Лево)
      glColor3f(0.0f, 0.0f, 1.0f);                      // Синий
      glVertex3f(-1.0f, -1.0f, -1.0f);                  // Лево треугольника (Лево)
      glColor3f(0.0f, 1.0f, 0.0f);                      // Зеленный
      glVertex3f(-1.0f, -1.0f, 1.0f);                  // Право треугольника (Лево)
      glEnd();

  /*    glLoadMatrixf(glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(5.5f, 0.0f, 0.0f)) * cam->GetView()));

      glTranslatef(-1.5f, 0.0f, -6.0f);                 // Сдвиг влево и вглубь экрана
      glBegin(GL_TRIANGLES);                          // Начало рисования пирамиды
      glColor3f(1.0f, 0.0f, 0.0f);                      // Красный
      glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Передняя)
      glColor3f(0.0f, 1.0f, 0.0f);                      // Зеленный
      glVertex3f(-1.0f, -1.0f, 1.0f);                  // Левая точка
      glColor3f(0.0f, 0.0f, 1.0f);                      // Синий
      glVertex3f(1.0f, -1.0f, 1.0f);                  // Правая точка
      glColor3f(1.0f, 0.0f, 0.0f);                      // Красная
      glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Правая)
      glColor3f(0.0f, 0.0f, 1.0f);                      // Синия
      glVertex3f(1.0f, -1.0f, 1.0f);                  // Лево треугольника (Правая)
      glColor3f(0.0f, 1.0f, 0.0f);                      // Зеленная
      glVertex3f(1.0f, -1.0f, -1.0f);                 // Право треугольника (Правая)
      glColor3f(1.0f, 0.0f, 0.0f);                      // Красный
      glVertex3f(0.0f, 1.0f, 0.0f);                  // Низ треугольника (Сзади)
      glColor3f(0.0f, 1.0f, 0.0f);                      // Зеленный
      glVertex3f(1.0f, -1.0f, -1.0f);                 // Лево треугольника (Сзади)
      glColor3f(0.0f, 0.0f, 1.0f);                      // Синий
      glVertex3f(-1.0f, -1.0f, -1.0f);                 // Право треугольника (Сзади)
      glColor3f(1.0f, 0.0f, 0.0f);                      // Красный
      glVertex3f(0.0f, 1.0f, 0.0f);                  // Верх треугольника (Лево)
      glColor3f(0.0f, 0.0f, 1.0f);                      // Синий
      glVertex3f(-1.0f, -1.0f, -1.0f);                  // Лево треугольника (Лево)
      glColor3f(0.0f, 1.0f, 0.0f);                      // Зеленный
      glVertex3f(-1.0f, -1.0f, 1.0f);                  // Право треугольника (Лево)
      glEnd();
      */
      REGISTRY.GetWindow().SwapBuffers();
      REGISTRY.GetWindow().GetMouse().Update();
      Window::WindowSystemPollEvents();
    }
  }

  return 0;
}
