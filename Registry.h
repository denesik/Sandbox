#pragma once

#ifndef Registry_h__
#define Registry_h__

#include <memory>
#include "Graphic/Render/Render.h"
#include "Graphic/Window/Window.h"

#define REGISTRY Registry::Instatce()

class Registry
{
public:
  static Registry &Instatce();

  Window &GetWindow();

  Render &GetRender();

private:
  Registry();
  ~Registry();
  Registry(const Registry &);
  Registry& operator=(const Registry &);

private:

  std::unique_ptr<Window> mWindow;
  std::unique_ptr<Render> mRender;

};

#endif // Registry_h__
