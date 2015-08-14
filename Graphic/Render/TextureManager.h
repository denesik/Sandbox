#pragma once

#ifndef TextureManager_h__
#define TextureManager_h__

#include "Texture.h"
#include <string>
#include <unordered_map>



/// Менеджер текстур.
/// Хранит все игровые текстуры.
class TextureManager
{
public:
  TextureManager(void);
  ~TextureManager(void);

  /// Загрузить указанную текстуру.
  /// Если текстура с таким именем существует, она не загружается.
  void LoadTexture(const std::string &name);

  /// Получить текстуру по имени.
  /// Если текстуры не существует, возвращается нулевой указатель.
  PTexture GetTexture(const std::string &name) const;

private:

  std::unordered_map<std::string, PTexture> mTextures;

};



#endif // TextureManager_h__
