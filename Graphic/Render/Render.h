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
  struct Version
  {
    int major = 0;
    int minor = 0;
  };

public:

  Render();
  ~Render();

  static void Initialize();

  void DrawSector(RenderSector &sector);

  const Version &GetVersion() const;

private:

  std::unique_ptr<Shader> mShader;
   
  Version mVersion;

};



#endif // Render_h__
