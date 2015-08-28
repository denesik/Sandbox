// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "RenderSector.h"


#include <GLFW\glfw3.h>
#include <iostream>
#include <assert.h>
#include <glm\gtc\matrix_transform.hpp>
#include "..\..\core\Sector.h"


class SectorFaceGenerator  
{
public:
  enum 
  {
    SIZE = SECTOR_SIZE * SECTOR_SIZE * 2 + 
    SECTOR_SIZE * (SECTOR_SIZE - 2) * 2 +
    (SECTOR_SIZE - 2) * (SECTOR_SIZE - 2) * 2,
  };
public:

  static const glm::uvec3 *Data() 
  {
    static SectorFaceGenerator generator;
    return generator.data;
  }

private:
  glm::uvec3 data[SIZE];
private:
  SectorFaceGenerator()
  {
    unsigned int index = 0;
    // left, right
    for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
      for (unsigned int y = 0; y < SECTOR_SIZE; ++y)
      {
        data[index++] = { 0, y, z };
        data[index++] = { SECTOR_SIZE - 1, y, z };
      }
    // front, back
    for (unsigned int y = 0; y < SECTOR_SIZE; ++y)
      for (unsigned int x = 1; x < SECTOR_SIZE - 1; ++x)
      {
        data[index++] = { x, y, SECTOR_SIZE - 1 };
        data[index++] = { x, y, 0 };
      }
    // top, bottom
    for (unsigned int z = 1; z < SECTOR_SIZE - 1; ++z)
      for (unsigned int x = 1; x < SECTOR_SIZE - 1; ++x)
      {
        data[index++] = { x, SECTOR_SIZE - 1, z };
        data[index++] = { x, 0, z };
      }
    assert(index == SIZE);
  }
  ~SectorFaceGenerator() {};
  SectorFaceGenerator(const SectorFaceGenerator &) = delete;
  SectorFaceGenerator& operator=(const SectorFaceGenerator &) = delete;
};



RenderSector::RenderSector(Sector &sector, const glm::ivec3 &pos)
  : mSector(sector), mModel(glm::translate({}, pos * static_cast<int>(SECTOR_SIZE)))
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

  glm::uvec3 pos(1);

  for (; pos.z < SECTOR_SIZE - 1; ++pos.z)
  {
    for (; pos.y < SECTOR_SIZE - 1; ++pos.y)
    {
      for (; pos.x < SECTOR_SIZE - 1; ++pos.x)
      {
        const auto block = mSector.GetBlock(pos);
        Model::Side sides = Model::EMPTY;
        if (block)
        {
          if (!mSector.GetBlock({ pos.z, pos.y, pos.x + 1 })) sides |= Model::RIGHT;
          if (!mSector.GetBlock({ pos.z, pos.y, pos.x - 1 })) sides |= Model::LEFT;
          if (!mSector.GetBlock({ pos.z, pos.y + 1, pos.x })) sides |= Model::TOP;
          if (!mSector.GetBlock({ pos.z, pos.y - 1, pos.x })) sides |= Model::BOTTOM;
          if (!mSector.GetBlock({ pos.z + 1, pos.y, pos.x })) sides |= Model::FRONT;
          if (!mSector.GetBlock({ pos.z - 1, pos.y, pos.x })) sides |= Model::BACK;
          
          if (sides)
          {
            sides == Model::ALL ? block->GetModel().FillBuffer(mBufferStatic, pos) :
                                  block->GetModel().FillBuffer(mBufferStatic, pos, sides);
          }
//          block->GetModel().FillBuffer(mBufferStatic, pos);
        }
      }
      pos.x = 1;
    }
    pos.y = 1;
  }

  for (unsigned int i = 0; i < SectorFaceGenerator::SIZE; ++i)
  {
    const auto &pos = static_cast<glm::ivec3>(SectorFaceGenerator::Data()[i]);
    const auto block = mSector.GetBlock(pos);
    Model::Side sides = Model::EMPTY;
    if (block)
    {
      if (!GetBlock({ pos.x + 1, pos.y, pos.z })) sides |= Model::RIGHT;
      if (!GetBlock({ pos.x - 1, pos.y, pos.z })) sides |= Model::LEFT;
      if (!GetBlock({ pos.x, pos.y + 1, pos.z })) sides |= Model::TOP;
      if (!GetBlock({ pos.x, pos.y - 1, pos.z })) sides |= Model::BOTTOM;
      if (!GetBlock({ pos.x, pos.y, pos.z + 1 })) sides |= Model::FRONT;
      if (!GetBlock({ pos.x, pos.y, pos.z - 1 })) sides |= Model::BACK;

      if (sides)
      {
        sides == Model::ALL ? block->GetModel().FillBuffer(mBufferStatic, pos) : 
                              block->GetModel().FillBuffer(mBufferStatic, pos, sides);
      }
    }
  }


  std::cout << "RenderGen: " << glfwGetTime() - currentTime << std::endl;

  currentTime = glfwGetTime();
  mBufferStatic.Compile();
  std::cout << "RenderCompile: " << glfwGetTime() - currentTime << std::endl;
}

const glm::mat4 & RenderSector::GetModel() const
{
  return mModel;
}

void RenderSector::Draw()
{
  if (mSector.GeometryChanged())
  {
    Generate();
    mSector.GeometryChangedReset();
  }
  mBufferStatic.Draw();
}

const IBlock * RenderSector::GetBlock(const glm::ivec3 &pos)
{
  if (pos.x >= 0 && pos.x < SECTOR_SIZE &&
      pos.y >= 0 && pos.y < SECTOR_SIZE && 
      pos.z >= 0 && pos.z < SECTOR_SIZE)
  {
    return mSector.GetBlock(pos);
  }
  return nullptr;
}
