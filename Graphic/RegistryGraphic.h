#pragma once

#ifndef RegistryGraphic_h__
#define RegistryGraphic_h__

#include <memory>
#include "Render/Render.h"
#include "Window/Window.h"
#include "Render/TextureManager.h"
#include "Render/Camera.h"

#define REGISTRY_GRAPHIC RegistryGraphic::Instatce()

class RegistryGraphic
{
public:
  static RegistryGraphic &Instatce();

  Window &GetWindow();

  Render &GetRender();

  TextureManager &GetTextureManager();

  Camera &GetCamera();

private:
  RegistryGraphic();
  ~RegistryGraphic();
  RegistryGraphic(const RegistryGraphic &);
  RegistryGraphic& operator=(const RegistryGraphic &);

private:

  std::unique_ptr<Window> mWindow;
  std::unique_ptr<Render> mRender;
  std::unique_ptr<TextureManager> mTextureManager;
  std::unique_ptr<Camera> mCamera;
};

#endif // RegistryGraphic_h__
