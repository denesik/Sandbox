#include "Texture.h"

#include "RenderErrorChecker.h"
#define GLEW_STATIC
#include <GL/glew.h>


Texture::Texture(const Bitmap &bitmap)
  : mTextureId(0), mSize(bitmap.GetSize())
{
  if(!mSize.x || !mSize.y || !IsPow2(mSize.x) || !IsPow2(mSize.y))
  {
    throw new TextureException(TextureException::INCORRECT_SIZE);
  }

  bool smoothing = true; 

  glGenTextures(1, &mTextureId);
  if(!mTextureId)
  {
    throw new TextureException(TextureException::TEXTURE_NOT_CREATED);
  }

  glBindTexture(GL_TEXTURE_2D, mTextureId);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smoothing ? GL_LINEAR : GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smoothing ? GL_LINEAR : GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mSize.x, mSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, &bitmap.GetRaw()[0]);
  RenderCheckErrors();

}

Texture::~Texture()
{
  glDeleteTextures(1, &mTextureId);
  RenderCheckErrors();
}

const glm::uvec2 & Texture::GetSize()
{
  return mSize;
}

void Texture::Set()
{
  glBindTexture(GL_TEXTURE_2D, mTextureId);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void Texture::Set(const Color &color)
{
  glBindTexture(GL_TEXTURE_2D, mTextureId);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

