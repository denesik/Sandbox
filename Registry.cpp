#include "Registry.h"

#include "Graphic/Window/Window.h"
#include "Graphic/Render/RenderErrorChecker.h"

Registry & Registry::Instatce()
{
  static Registry registry;
  return registry;
}

Registry::Registry()
{
  Window::WindowSystemInitialize();

  try
  {
    mWindow.reset(new Window);
    mWindow->SetCurrentContext();
  }
  catch (WindowException *e)
  {
    printf("%s\n", e->what());
    return;
  }

  try
  {
    Render::Initialize();
  }
  catch (RenderException *e)
  {
    printf("%s\n", e->what());
    return;
  }

  mRender.reset(new Render);
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
