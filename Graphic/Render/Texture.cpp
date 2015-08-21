#include "Texture.h"

#include "RenderErrorChecker.h"
#include <GL/glew.h>


Texture::Texture(const Bitmap &bitmap)
  : mTextureId(0), mSize(bitmap.GetSize())
{
  if(!mSize.x || !mSize.y || !IsPow2(mSize.x) || !IsPow2(mSize.y))
  {
    throw "Texture not created. Incorrect size.";
  }

  bool smoothing = false; 

  glGenTextures(1, &mTextureId);
  if(!mTextureId)
  {
    throw "Texture not created. GL error.";
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

void Texture::Set(TextureSlot slot)
{
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, mTextureId);
}

