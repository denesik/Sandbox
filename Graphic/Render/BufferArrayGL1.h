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

private:

  unsigned int mList;

};

template<class VertexType>
BufferArrayGL1<VertexType>::BufferArrayGL1(const std::vector<VertexType> &vertexBuffer,
  const std::vector<unsigned int> &indexBuffer)
  : mVertexBuffer(vertexBuffer), mIndexBuffer(indexBuffer)
{
  mList = glGenLists(1);
}

template<class VertexType>
BufferArrayGL1<VertexType>::~BufferArrayGL1()
{
  glDeleteLists(mList, 1);
}

template<class VertexType>
void BufferArrayGL1<VertexType>::EnableAttribute(AttributeType type, unsigned int size, unsigned int offset)
{

}

template<class VertexType>
void BufferArrayGL1<VertexType>::Compile()
{
  glNewList(mList, GL_COMPILE);
  glBegin(GL_TRIANGLES);
  for (unsigned int i = 0; i < mIndexBuffer.size(); i += 3)
  {
    glTexCoord2fv(reinterpret_cast<const GLfloat *>(&mVertexBuffer[mIndexBuffer[i + 0]].texture));
    glVertex3fv(reinterpret_cast<const GLfloat *>(&mVertexBuffer[mIndexBuffer[i + 0]].vertex));
    glTexCoord2fv(reinterpret_cast<const GLfloat *>(&mVertexBuffer[mIndexBuffer[i + 1]].texture));
    glVertex3fv(reinterpret_cast<const GLfloat *>(&mVertexBuffer[mIndexBuffer[i + 1]].vertex));
    glTexCoord2fv(reinterpret_cast<const GLfloat *>(&mVertexBuffer[mIndexBuffer[i + 2]].texture));
    glVertex3fv(reinterpret_cast<const GLfloat *>(&mVertexBuffer[mIndexBuffer[i + 2]].vertex));
  }
  glEnd();
  glEndList();
}

template<class VertexType>
void BufferArrayGL1<VertexType>::Draw()
{
  glCallList(mList);
}

#endif // BufferArrayGL1_h__

