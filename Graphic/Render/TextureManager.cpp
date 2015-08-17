#include "TextureManager.h"

#include "Bitmap.h"
#include <iostream>

TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
}

void TextureManager::LoadTexture(const std::string &name)
{
  if(mTextures.find(name) != mTextures.end())
  {
    // Текстура уже существует.
    std::cout << "LoadTexture error" << std::endl;
    return;
  }

  try
  {
    // Грузим текстуру с фс.
    Bitmap bitmap(name);
    mTextures[name] = PTexture(new Texture(bitmap));
  }
  catch(char *msg)
  {
    std::cout << msg << std::endl;
  }
}

PTexture TextureManager::GetTexture(const std::string &name) const
{
  auto itTexture = mTextures.find(name);
  if(itTexture == mTextures.end())
  {
    // Текстура не найдена.
    return nullptr;
  }

  return (*itTexture).second;
}
