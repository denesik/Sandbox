#pragma once

#ifndef Render_h__
#define Render_h__

#include "Color.h"
#include "Texture.h"
#include "Camera.h"

class RenderException: public std::exception
{
public:
  RenderException(unsigned int id)
    : mId(id)
  {
  }
  virtual const char *what() const throw()
  {
    return "Render exception";
  }

  enum
  {
    RENDER_NOT_INITIALIZED,

    COUNT,
  };

private:
  const unsigned int mId;
};



class Render
{
public:

  Render();
  ~Render();

  static void Initialize();

  /// Рисовать с помощью данной камеры.
  void UseCam(const PCamera &camera);



private:

  PCamera mCamera;

};



#endif // Render_h__
