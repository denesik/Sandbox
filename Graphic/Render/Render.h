// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Render_h__
#define Render_h__

#include "Color.h"
#include "Texture.h"
#include "Camera.h"
#include "Shader.h"
#include "RenderSector.h"



class Render
{
public:

  Render();
  ~Render();

  static void Initialize();

  void DrawSector(RenderSector &sector);

private:

  std::unique_ptr<Shader> mShader;

};



#endif // Render_h__
