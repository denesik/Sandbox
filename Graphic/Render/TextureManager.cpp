#include "TextureManager.h"

#include "Bitmap.h"

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
    printf("LoadTexture error\n");
    // Текстура уже существует.
    return;
  }

  try
  {
    // Грузим текстуру с фс.
    Bitmap bitmap(name);
    mTextures[name] = PTexture(new Texture(bitmap));
  }
  catch(BitmapException *)
  {
    printf("LoadTexture error\n");
  	// Ошибка создания текстуры.
  }
  catch(TextureException *)
  {
    printf("LoadTexture error\n");
    // Ошибка создания текстуры.
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
