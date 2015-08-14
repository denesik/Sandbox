#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include <glm/glm.hpp>
#include "Bitmap.h"
#include "Color.h"

class TextureException: public std::exception
{
public:
  TextureException(unsigned int id)
    : mId(id)
  {
  }
  virtual const char *what() const throw()
  {
    return "Texture exception";
  }

  enum
  {
    INCORRECT_SIZE,
    TEXTURE_NOT_CREATED,

    COUNT,
  };

private:
  const unsigned int mId;
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

  /// Установить текстуру.
  void Set();

  /// Установить текстуру и смешать с указанным цветом.
  void Set(const Color &color);

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
