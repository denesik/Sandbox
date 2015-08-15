#include "Registry.h"

#include "Graphic/Window/Window.h"
#include "Graphic/Render/RenderErrorChecker.h"
#include <iostream>

Registry &Registry::Instatce()
{
  static Registry registry;
  return registry;
}

Registry::Registry()
{
  Window::WindowSystemInitialize();
  try
  {
    mWindow = std::make_unique<Window>(glm::uvec2(600, 600));
    mWindow->SetCurrentContext();
    Render::Initialize();
  }
  catch (const char *)
  {
    throw;
  }

  mRender = std::make_unique<Render>();
}

Registry::~Registry()
{
  Window::WindowSystemFinally();
}

Window &Registry::GetWindow()
{
  return *mWindow.get();
}

Render &Registry::GetRender()
{
  return *mRender;
}
