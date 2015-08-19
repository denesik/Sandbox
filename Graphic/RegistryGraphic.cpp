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
  mTextureManager = std::make_unique<TextureManager>();
}

RegistryGraphic::~RegistryGraphic()
{
  mTextureManager.reset();
  mRender.reset();
  mWindow.reset();
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

TextureManager & RegistryGraphic::GetTextureManager()
{
  return *mTextureManager;
}
