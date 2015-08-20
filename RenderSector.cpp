#include "RenderSector.h"


#include <GLFW\glfw3.h>
#include <iostream>

RenderSector::RenderSector(const Sector &sector)
  : mSector(sector)
{
  mBufferStatic.EnableAttribute(ATTRIBUTE_VERTEX, sizeof(VertexVT::vertex), offsetof(VertexVT, vertex));
  mBufferStatic.EnableAttribute(ATTRIBUTE_TEXTURE, sizeof(VertexVT::texture), offsetof(VertexVT, texture));
}


RenderSector::~RenderSector()
{
}

void RenderSector::Generate()
{
  auto &vertex = mBufferStatic.Vertex();
  auto &index = mBufferStatic.Index();

  auto currentTime = glfwGetTime();

  vertex.clear();
  index.clear();

  const auto &map = mSector.mMap;

  glm::uvec3 pos;

  for (; pos.z < SECTOR_SIZE; ++pos.z)
  {
    for (; pos.y < SECTOR_SIZE; ++pos.y)
    {
      for (; pos.x < SECTOR_SIZE; ++pos.x)
      {
        const auto block = map[pos.z][pos.y][pos.x];
        if (block)
        {
          block->GetModel().FillBuffer(mBufferStatic, pos);
        }
      }
      pos.x = 0;
    }
    pos.y = 0;
  }


  std::cout << "RenderGen: " << glfwGetTime() - currentTime << std::endl;

  currentTime = glfwGetTime();
  mBufferStatic.Compile();
  std::cout << "RenderCompile: " << glfwGetTime() - currentTime << std::endl;
}

BufferArray<VertexVT> & RenderSector::GetBuffer()
{
  return mBufferStatic;
}
