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

  void SetAttribute(AttributeType type, unsigned int size, unsigned int offset);

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

  struct Attribute
  {
    AttributeType type;     // Номер атрибута в шейдере.
    unsigned int size;      // Размер атрибута в байтах.
    unsigned int offset;    // Смещение атрибута относительно начала вершины в байтах.
  };

};

template<class VertexType>
void BufferArray<VertexType>::Draw()
{
  glBindVertexArray(mVao);
  glDrawElements(GL_TRIANGLES, mIndexBuffer.size(), GL_UNSIGNED_INT, NULL);
}

template<class VertexType>
void BufferArray<VertexType>::SetAttribute(AttributeType type, unsigned int size, unsigned int offset)
{
  glBindVertexArray(mVao);
  glEnableVertexAttribArray(type);
  glVertexAttribPointer(type, size, GL_FLOAT, GL_FALSE, sizeof(VertexType), (void*)(sizeof(float) * offset));
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
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType) * mVertexBuffer.size(), &mVertexBuffer[0], GL_STATIC_DRAW);

  glGenBuffers(1, &mVbi);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVbi);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndexBuffer.size(), &mIndexBuffer[0], GL_STATIC_DRAW);
}


