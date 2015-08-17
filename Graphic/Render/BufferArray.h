#pragma once

#define GLEW_STATIC
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <vector>


enum AttributeType
{
  ATTRIBUTE_VERTEX = 0,
  ATTRIBUTE_COLOR = 1,
  ATTRIBUTE_TEXTURE = 2,

  ATTRIBUTE_LAST = ATTRIBUTE_TEXTURE
};


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

  unsigned int mVao = 0;
  unsigned int mVbo = 0;
  unsigned int mVbi = 0;

};

template<class VertexType>
BufferArray<VertexType>::BufferArray()
{
  glGenVertexArrays(1, &mVao);
  glGenBuffers(1, &mVbo);
  glGenBuffers(1, &mVbi);
  glBindVertexArray(mVao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbi);
}

template<class VertexType>
BufferArray<VertexType>::~BufferArray()
{
  glDeleteBuffers(1, &mVbi);
  glDeleteBuffers(1, &mVbo);
  glDeleteVertexArrays(1, &mVao);
}

template<class VertexType>
void BufferArray<VertexType>::Draw()
{
  glBindVertexArray(mVao);
  glDrawElements(GL_TRIANGLES, mIndexBuffer.size(), GL_UNSIGNED_INT, NULL);
}

template<class VertexType>
void BufferArray<VertexType>::EnableAttribute(AttributeType type, unsigned int size, unsigned int offset)
{
  glBindVertexArray(mVao);
  glBindBuffer(GL_ARRAY_BUFFER, mVbo);
  glEnableVertexAttribArray(type);
  glVertexAttribPointer(type, size, GL_FLOAT, GL_FALSE, sizeof(VertexType), (void*)(sizeof(float) * offset));
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
void BufferArray<VertexType>::Compile()
{
  glBindBuffer(GL_ARRAY_BUFFER, mVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType) * mVertexBuffer.size(), &mVertexBuffer[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbi);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndexBuffer.size(), &mIndexBuffer[0], GL_STATIC_DRAW);
}


