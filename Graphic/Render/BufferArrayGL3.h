// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef BufferArrayGL3_h__
#define BufferArrayGL3_h__

#include "..\..\IBufferArrayGL.h"

template<class VertexType>
class BufferArrayGL3 : public IBufferArrayGL
{
public:
  BufferArrayGL3(const std::vector<VertexType> &vertexBuffer, const std::vector<unsigned int> &indexBuffer);
  ~BufferArrayGL3();

  /// Включить и настроить атрибут.
  void EnableAttribute(AttributeType type, unsigned int size, unsigned int offset);

  /// Скомпилировать буфер в видеопамяти.
  void Compile();

  /// нарисовать буфер.
  void Draw();

protected:

  const std::vector<VertexType> &mVertexBuffer;

  const std::vector<unsigned int> &mIndexBuffer;

  unsigned int mVao = 0;
  unsigned int mVbo = 0;
  unsigned int mVbi = 0;

};

template<class VertexType>
BufferArrayGL3<VertexType>::BufferArrayGL3(const std::vector<VertexType> &vertexBuffer, 
  const std::vector<unsigned int> &indexBuffer)
  : mVertexBuffer(vertexBuffer), mIndexBuffer(indexBuffer)
{
  glGenVertexArrays(1, &mVao);
  glGenBuffers(1, &mVbo);
  glGenBuffers(1, &mVbi);
  glBindVertexArray(mVao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbi);
}

template<class VertexType>
BufferArrayGL3<VertexType>::~BufferArrayGL3()
{
  glDeleteBuffers(1, &mVbi);
  glDeleteBuffers(1, &mVbo);
  glDeleteVertexArrays(1, &mVao);
}

template<class VertexType>
void BufferArrayGL3<VertexType>::EnableAttribute(AttributeType type, unsigned int size, unsigned int offset)
{
  glBindVertexArray(mVao);
  glBindBuffer(GL_ARRAY_BUFFER, mVbo);
  glVertexAttribPointer(type, size / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(VertexType), (char *)NULL + offset);
  glEnableVertexAttribArray(type);
}

template<class VertexType>
void BufferArrayGL3<VertexType>::Compile()
{
  glBindBuffer(GL_ARRAY_BUFFER, mVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType) * mVertexBuffer.size(), &mVertexBuffer[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbi);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndexBuffer.size(), &mIndexBuffer[0], GL_STATIC_DRAW);
}

template<class VertexType>
void BufferArrayGL3<VertexType>::Draw()
{
  glBindVertexArray(mVao);
  glDrawElements(GL_TRIANGLES, mIndexBuffer.size(), GL_UNSIGNED_INT, NULL);
}


#endif // BufferArrayGL3_h__

