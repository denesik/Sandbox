﻿// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include <glm/glm.hpp>
#include "Bitmap.h"
#include "Color.h"

/// Описание текстурных слотов.
enum TextureSlot
{
  TEXTURE_SLOT_0,
  TEXTURE_SLOT_1,
  TEXTURE_SLOT_2,
  TEXTURE_SLOT_3,
  TEXTURE_SLOT_4,
  TEXTURE_SLOT_5,
  TEXTURE_SLOT_6,
  TEXTURE_SLOT_7,

  TEXTURE_SLOT_COUNT,
};

class Texture;
typedef std::shared_ptr<Texture> PTexture;

/// Текстура. Находится в видеопамяти.
class Texture
{
public:
  /// Создать текстуру на основе битмапы.
  Texture(const Bitmap &bitmap);

  /// Разрушить текстуру.
  ~Texture();

  /// Вернуть размер текстуры.
  const glm::uvec2 &GetSize();

  /// Установить текстуру на заданный текстурный слот.
  void Set(TextureSlot slot);

private:
  // id текстуры. 0 - не существующая текстура.
  unsigned int mTextureId;

  // Размер текстуры в текстелях.
  glm::uvec2 mSize;

private:

  // Вспомогательная функция. Узнает, является ли число степенью 2.
  bool IsPow2(unsigned int a)
  {
    return !(a & (a - 1));
  }

};


#endif // TEXTURE_H
