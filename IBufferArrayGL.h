// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef IBufferArrayGL_h__
#define IBufferArrayGL_h__

enum AttributeType
{
  ATTRIBUTE_VERTEX = 1,
  ATTRIBUTE_COLOR = 2,
  ATTRIBUTE_TEXTURE = 3,

  ATTRIBUTE_LAST = ATTRIBUTE_TEXTURE
};

class IBufferArrayGL
{
public:
  IBufferArrayGL() {};
  virtual ~IBufferArrayGL() {};

  /// Включить и настроить атрибут.
  virtual void EnableAttribute(AttributeType type, unsigned int size, unsigned int offset) = 0;

  /// Скомпилировать буфер в видеопамяти.
  virtual void Compile() = 0;

  /// нарисовать буфер.
  virtual void Draw() = 0;

private:
  IBufferArrayGL(const IBufferArrayGL &) = delete;
  IBufferArrayGL &operator=(const IBufferArrayGL &) = delete;
};


#endif // IBufferArrayGL_h__

