#pragma once

#define GLEW_STATIC
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <vector>

struct VertexTest
{
  glm::vec3 vertex;
  glm::vec2 texture;
};

struct Attribute
{
  unsigned int index;     // Номер атрибута в шейдере.
  unsigned int size;      // Размер атрибута в байтах.
  unsigned int offset;    // Смещение атрибута относительно начала вершины в байтах.
};

template<class VertexType>
class BufferArray
{
public:
  BufferArray();
  ~BufferArray();

  void SetAttribute(const Attribute &attribute);

  void Compile();

  void Draw();

  std::vector<VertexType> &Vertex();

  std::vector<unsigned int> &Index();

private:

  std::vector<VertexType> mVertexBuffer;

  std::vector<unsigned int> mIndexBuffer;

  unsigned int mVao = 0;
  unsigned int mVbo = 0;
  unsigned int mVbi = 0;
};

template<class VertexType>
void BufferArray<VertexType>::Draw()
{
  glBindVertexArray(mVao);
  glDrawElements(GL_TRIANGLES, mIndexBuffer.size(), GL_UNSIGNED_INT, NULL);
}

template<class VertexType>
void BufferArray<VertexType>::SetAttribute(const Attribute &attribute)
{
  glBindVertexArray(mVao);
  glEnableVertexAttribArray(attribute.index);
  glVertexAttribPointer(attribute.index, attribute.size, GL_FLOAT, GL_FALSE, sizeof(VertexType), (void*)(sizeof(float) * attribute.offset));
}

template<class VertexType>
BufferArray<VertexType>::BufferArray()
{
  glGenVertexArrays(1, &mVao);
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
void BufferArray<VertexType>::Compile()
{
  glBindVertexArray(mVao);

  glGenBuffers(1, &mVbo);
  glBindBuffer(GL_ARRAY_BUFFER, mVbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(VertexType), &mVertexBuffer[0], GL_STATIC_DRAW);

  unsigned int mVbi = 0;
  glGenBuffers(1, &mVbi);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbi);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndexBuffer.size(), &mIndexBuffer[0], GL_STATIC_DRAW);
}


