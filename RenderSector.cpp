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

  //auto currentTime = glfwGetTime();

  vertex.clear();
  index.clear();

  const auto &map = mSector.mMap;

  glm::uvec3 pos(1);

  for (; pos.z < SECTOR_SIZE - 1; ++pos.z)
  {
    for (; pos.y < SECTOR_SIZE - 1; ++pos.y)
    {
      for (; pos.x < SECTOR_SIZE - 1; ++pos.x)
      {
        const auto block = map[pos.z][pos.y][pos.x];
        Model::Side sides = Model::EMPTY;
        if (block)
        {
          if (!map[pos.z][pos.y][pos.x + 1]) sides |= Model::RIGHT;
          if (!map[pos.z][pos.y][pos.x - 1]) sides |= Model::LEFT;
          if (!map[pos.z][pos.y + 1][pos.x]) sides |= Model::TOP;
          if (!map[pos.z][pos.y - 1][pos.x]) sides |= Model::BOTTOM;
          if (!map[pos.z + 1][pos.y][pos.x]) sides |= Model::FRONT;
          if (!map[pos.z - 1][pos.y][pos.x]) sides |= Model::BACK;
          
          if (sides)
          {
            block->GetModel().FillBuffer(mBufferStatic, pos, sides);
          }
        }
      }
      pos.x = 1;
    }
    pos.y = 1;
  }

  // left, right
  for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
  for (unsigned int y = 0; y < SECTOR_SIZE; ++y)
  {
    if (map[z][y][0]) map[z][y][0]->GetModel().FillBuffer(mBufferStatic, {0, y, z});
    if (map[z][y][SECTOR_SIZE - 1]) map[z][y][SECTOR_SIZE - 1]->GetModel().FillBuffer(mBufferStatic, {SECTOR_SIZE - 1, y, z});
  }
  // front, back
  for (unsigned int y = 0; y < SECTOR_SIZE; ++y)
  for (unsigned int x = 1; x < SECTOR_SIZE - 1; ++x)
  {
    if (map[0][y][x]) map[0][y][x]->GetModel().FillBuffer(mBufferStatic, { x, y, 0});
    if (map[SECTOR_SIZE - 1][y][x]) map[SECTOR_SIZE - 1][y][x]->GetModel().FillBuffer(mBufferStatic, { x, y, SECTOR_SIZE - 1 });
  }
  // top, bottom
  for (unsigned int z = 1; z < SECTOR_SIZE - 1; ++z)
  for (unsigned int x = 1; x < SECTOR_SIZE - 1; ++x)
  {
    if (map[z][0][x]) map[z][0][x]->GetModel().FillBuffer(mBufferStatic, { x, 0, z });
    if (map[z][SECTOR_SIZE - 1][x]) map[z][SECTOR_SIZE - 1][x]->GetModel().FillBuffer(mBufferStatic, { x, SECTOR_SIZE - 1, z });
  }


  //std::cout << "RenderGen: " << glfwGetTime() - currentTime << std::endl;

  //currentTime = glfwGetTime();
  mBufferStatic.Compile();
  //std::cout << "RenderCompile: " << glfwGetTime() - currentTime << std::endl;
}

BufferArray<VertexVT> & RenderSector::GetBuffer()
{
  return mBufferStatic;
}
