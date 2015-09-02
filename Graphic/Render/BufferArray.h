// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef BufferArray_h__
#define BufferArray_h__


#include <gl/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "BufferArrayGL3.h"
#include "BufferArrayGL1.h"



template<class VertexType>
class BufferArray
{
public:
  BufferArray();
  ~BufferArray();

  /// Включить и настроить атрибут.
  void EnableAttribute(AttributeType type, unsigned int size, unsigned int offset);

  /// Скомпилировать буфер в видеопамяти.
  void Compile();

  /// нарисовать буфер.
  void Draw();

  /// Буфер вершин.
  std::vector<VertexType> &Vertex();

  /// Буфер индексов.
  std::vector<unsigned int> &Index();

private:

  std::vector<VertexType> mVertexBuffer;

  std::vector<unsigned int> mIndexBuffer;

  std::unique_ptr<IBufferArrayGL> mBuffer;

};

template<class VertexType>
BufferArray<VertexType>::BufferArray()
{
  int major = 0;
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  if (major < 3)
  {
    mBuffer.reset(new BufferArrayGL1<VertexType>(mVertexBuffer, mIndexBuffer));
  }
  else
  {
    mBuffer.reset(new BufferArrayGL3<VertexType>(mVertexBuffer, mIndexBuffer));
  }
}

template<class VertexType>
BufferArray<VertexType>::~BufferArray()
{

}

template<class VertexType>
std::vector<unsigned int> & BufferArray<VertexType>::Index()
{
  return mIndexBuffer;
}

template<class VertexType>
std::vector<VertexType> & BufferArray<VertexType>::Vertex()
{
  return mVertexBuffer;
}

template<class VertexType>
void BufferArray<VertexType>::Draw()
{
  mBuffer->Draw();
}

template<class VertexType>
void BufferArray<VertexType>::Compile()
{
  mBuffer->Compile();
}

template<class VertexType>
void BufferArray<VertexType>::EnableAttribute(AttributeType type, unsigned int size, unsigned int offset)
{
  mBuffer->EnableAttribute(type, size, offset);
}


#endif // BufferArray_h__

