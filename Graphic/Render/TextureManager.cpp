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
  LoadTexture(std::vector<std::string>({name}));
}


void TextureManager::LoadTexture(const std::vector<std::string> &names)
{
  for (unsigned int i = 0; i < mMultiAtlas.size(); ++i)
  {
    if (LoadToAtlas(i, names))
    {
      // Кажется мы смогли загрузить все текстуры в один атлас.
      return;
    }
  }
  // Мы пытались, но не смоги...
  // Попробуем создать еще один атлас.
  mMultiAtlas.resize(mMultiAtlas.size() + 1);
  if (!LoadToAtlas(mMultiAtlas.size() - 1, names))
  {
    // Ошибка.
    std::cout << "TextureManager. Load texture error." << std::endl;
  }
}

std::tuple<PTexture, glm::uvec4> TextureManager::GetTexture(const std::string &name) const
{
  auto itTexture = mTextures.find(name);
  if (itTexture == mTextures.end())
  {
    // Текстура не найдена.
    return std::make_tuple<PTexture, glm::uvec4>(nullptr, {});
  }

  return std::tuple<PTexture, glm::uvec4>(mMultiAtlas[(*itTexture).second.index].texture, (*itTexture).second.pos);
}

void TextureManager::Compile()
{
  for (auto &i : mMultiAtlas)
  {
    i.texture = std::make_shared<Texture>(i.atlas.GetAtlas());
  }
}

bool TextureManager::LoadToAtlas(unsigned int atlas, const std::vector<std::string> &names)
{
  // TODO: Удаление из атласа, если не смогли вставить.
  for (auto &i : names)
  {
    auto pos = mMultiAtlas[atlas].atlas.Add(i);
    mTextures[i] = { atlas, pos };
  }

  return true;
}
