#ifndef WINDOW_GL_H
#define WINDOW_GL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Keyboard.h"
#include "Mouse.h"
#include <functional>

class WindowException: public std::exception
{
public:
  WindowException(unsigned int id)
    : mId(id)
  {
  }
  virtual const char *what() const throw()
  {
    return "Window exception";
  }

  enum
  {
    WINDOW_SYSTEM_NOT_INICIALIZED,
    NOT_CREATED,

    COUNT,
  };

private:
  const unsigned int mId;
};


class Window
{
public:
  Window();
  ~Window();

  /// Инициализация оконной системы.
  static void WindowSystemInitialize();

  /// Завершить работу с оконной системой.
  static void WindowSystemFinally();

  /// Обработать события.
  static void WindowSystemPollEvents();

  /// Установить текущий контекст для данного окна.
  void SetCurrentContext();

  /// Должно ли окно закрыться?
  bool WindowShouldClose();

  /// Переключить буферы.
  void SwapBuffers();

  Keyboard &GetKeyboard();

  void SetResizeCallback(std::function<void(glm::uvec2)> callback);

  void SetTitle(const std::string &title);

  Mouse &GetMouse();

private:

  struct WindowDeleter
  {
    void operator()(GLFWwindow *window) const
    {
      printf("window delete\n");
      glfwDestroyWindow(window);
    }
  };

  std::unique_ptr<GLFWwindow, WindowDeleter> mWindow;

  std::unique_ptr<Keyboard> mKeyboard;

  Mouse mMouse;

  std::function<void(glm::uvec2)> mResizeCallback;

private:

  // Функции обратного вызова для glfw.
  static void GlfwErrorCallback(int ,const char* description);
  static void GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
  static void GlfwCursorPosCallback(GLFWwindow *window, double x, double y);
  static void GlfwResizeCallback(GLFWwindow* window, int width, int height);
};

#endif // WINDOW_GL_H
