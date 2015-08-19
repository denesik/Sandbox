#include "RegistryGraphic.h"

#include "Render/RenderErrorChecker.h"
#include <iostream>

RegistryGraphic &RegistryGraphic::Instatce()
{
  static RegistryGraphic registry;
  return registry;
}

RegistryGraphic::RegistryGraphic()
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

RegistryGraphic::~RegistryGraphic()
{
  Window::WindowSystemFinally();
}

Window &RegistryGraphic::GetWindow()
{
  return *mWindow.get();
}

Render &RegistryGraphic::GetRender()
{
  return *mRender;
}
