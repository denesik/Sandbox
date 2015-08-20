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

//   vertex.reserve(80000);
//   index.reserve(1120000);

  const auto &map = mSector.mMap;

  for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
  for (unsigned int y = 0; y < SECTOR_SIZE; ++y)
  for (unsigned int x = 0; x < SECTOR_SIZE; ++x)
  {
    if (map[z][y][x])
    {
      const Model &model = map[z][y][x]->GetModel();
      const auto &blockVertex = model.GetVertex();
      const auto &blockIndex = model.GetIndex();

      unsigned int vertexIndex = vertex.size();
      for (unsigned int i = 0; i < blockVertex.size(); ++i)
      {
        vertex.push_back(
        {
          {
            blockVertex[i].vertex.x + x,
            blockVertex[i].vertex.y + y,
            blockVertex[i].vertex.z + z
          } ,
          blockVertex[i].texture
        });
      }
      for (unsigned int i = 0; i < blockIndex.size(); ++i)
      {
        index.push_back(vertexIndex + blockIndex[i]);
      }
    }
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
