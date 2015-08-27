// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef BufferArrayGL1_h__
#define BufferArrayGL1_h__


#include "..\..\IBufferArrayGL.h"

template<class VertexType>
class BufferArrayGL1 : public IBufferArrayGL
{
public:
  BufferArrayGL1(const std::vector<VertexType> &vertexBuffer, const std::vector<unsigned int> &indexBuffer);
  ~BufferArrayGL1();

  /// Включить и настроить атрибут.
  void EnableAttribute(AttributeType type, unsigned int size, unsigned int offset);

  /// Скомпилировать буфер в видеопамяти.
  void Compile();

  /// нарисовать буфер.
  void Draw();

protected:

  const std::vector<VertexType> &mVertexBuffer;

  const std::vector<unsigned int> &mIndexBuffer;

};

template<class VertexType>
BufferArrayGL1<VertexType>::BufferArrayGL1(const std::vector<VertexType> &vertexBuffer,
  const std::vector<unsigned int> &indexBuffer)
  : mVertexBuffer(vertexBuffer), mIndexBuffer(indexBuffer)
{
}

template<class VertexType>
BufferArrayGL1<VertexType>::~BufferArrayGL1()
{
}

template<class VertexType>
void BufferArrayGL1<VertexType>::EnableAttribute(AttributeType type, unsigned int size, unsigned int offset)
{

}

template<class VertexType>
void BufferArrayGL1<VertexType>::Compile()
{
 
}

template<class VertexType>
void BufferArrayGL1<VertexType>::Draw()
{
}
#endif // BufferArrayGL1_h__

