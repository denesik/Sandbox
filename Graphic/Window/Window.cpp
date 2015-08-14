#include "Window.h"

#include <stdio.h>
#include <assert.h>

Window::Window()
  : mKeyboard(new Keyboard())
{
  printf("Start window creating\n");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_SAMPLES, 4);

  GLFWmonitor *monitor = nullptr;

  mWindow = (decltype(mWindow))(glfwCreateWindow(600, 600, "title", monitor, nullptr));

  if (!mWindow)
  {
    throw new WindowException(WindowException::NOT_CREATED);
  }

  /// Привязываем к glfw окну указатель на объект WindowGL.
  glfwSetWindowUserPointer(mWindow.get(), this);

  glfwSetKeyCallback(mWindow.get(), &GlfwKeyCallback);
  glfwSetCursorPosCallback(mWindow.get(), &GlfwCursorPosCallback);

  //glfwSwapInterval(0);
  printf("Window created\n");
}

Window::~Window()
{
}

void Window::GlfwErrorCallback(int ,const char* description)
{
  printf("glfw error: %s\n", description);
}

void Window::GlfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  Window *windowGL = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if(windowGL)
  {
    windowGL->mKeyboard->SetKey(key, scancode, action, mods);
  }
}

void Window::GlfwCursorPosCallback(GLFWwindow *window, double x, double y)
{
  Window *windowGL = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if(windowGL)
  {
    windowGL->mMouse.SetPos(glm::vec2(static_cast<float>(x), static_cast<float>(y)));
  }
}

void Window::GlfwResizeCallback(GLFWwindow* window, int width, int height)
{
  Window *windowGL = static_cast<Window *>(glfwGetWindowUserPointer(window));
  if(windowGL && windowGL->mResizeCallback)
  {
    windowGL->mResizeCallback(glm::uvec2(width, height));
  }
}

void Window::WindowSystemInitialize()
{
  //glfwSetErrorCallback([](int ,const char* description){printf("%s\n", description);});

  glfwSetErrorCallback(&GlfwErrorCallback);

  if (glfwInit() != GL_TRUE)
  {
    throw new WindowException(WindowException::WINDOW_SYSTEM_NOT_INICIALIZED);
  }
}

void Window::WindowSystemFinally()
{
  glfwTerminate();
}

void Window::WindowSystemPollEvents()
{
  glfwPollEvents();
}

void Window::SetCurrentContext()
{
  assert(mWindow);
  glfwMakeContextCurrent(mWindow.get());

  // get version info
  const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
  const GLubyte* version = glGetString (GL_VERSION); // version as a string
  printf("Renderer: %s\n", renderer);
  printf("OpenGL version supported %s\n", version);
}

bool Window::WindowShouldClose()
{
  assert(mWindow);
  return glfwWindowShouldClose(mWindow.get()) == GL_TRUE;
}

void Window::SwapBuffers()
{
  assert(mWindow);
  glfwSwapBuffers(mWindow.get());
}

Keyboard &Window::GetKeyboard()
{
  return *mKeyboard;
}

void Window::SetResizeCallback(std::function<void(glm::uvec2)> callback)
{
  mResizeCallback = callback;
}

void Window::SetTitle(const std::string &title)
{
  assert(mWindow);
  glfwSetWindowTitle(mWindow.get(), title.c_str());
}

Mouse & Window::GetMouse()
{
  return mMouse;
}





