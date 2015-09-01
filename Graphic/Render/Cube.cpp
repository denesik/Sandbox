// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Cube.h"


#include "../RegistryGraphic.h"
#include <iostream>

static glm::vec3 vertexCube[] =
{
  { -0.5f, -0.5f,  0.5f },{ -0.5f,  0.5f,  0.5f },{ 0.5f,  0.5f,  0.5f },{ 0.5f, -0.5f,  0.5f }, // front
  { 0.5f, -0.5f,  0.5f },{ 0.5f,  0.5f,  0.5f },{ 0.5f,  0.5f, -0.5f },{ 0.5f, -0.5f, -0.5f }, // right
  { 0.5f, -0.5f, -0.5f },{ 0.5f,  0.5f, -0.5f },{ -0.5f,  0.5f, -0.5f },{ -0.5f, -0.5f, -0.5f }, // back
  { -0.5f, -0.5f, -0.5f },{ -0.5f,  0.5f, -0.5f },{ -0.5f,  0.5f,  0.5f },{ -0.5f, -0.5f,  0.5f }, // left
  { -0.5f,  0.5f,  0.5f },{ -0.5f,  0.5f, -0.5f },{ 0.5f,  0.5f, -0.5f },{ 0.5f,  0.5f,  0.5f }, // top
  { -0.5f, -0.5f, -0.5f },{ -0.5f, -0.5f,  0.5f },{ 0.5f, -0.5f,  0.5f },{ 0.5f, -0.5f, -0.5f }  // bot
};

static unsigned int indexCubeSide[] =
{
  0, 3, 2, 2, 1, 0
};

static glm::vec2 textureCube[] =
{
  { 0.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f },{ 1.0f, 0.0f }
};

Cube::Cube()
{
  mVertex.reserve(24);
  for (unsigned int i = 0; i < 24; ++i)
  {
    mVertex.push_back({ vertexCube[i] , textureCube[i % 4] });
  }
  mIndex.reserve(36);
  for (unsigned int i = 0; i < 6; ++i)
  {
    for (unsigned int j = 0; j < 6; ++j)
    {
      mIndex.push_back(i * 4 + indexCubeSide[j]);
    }
  }
}


Cube::~Cube()
{
}

void Cube::SetTexture(Side side, const std::string &name)
{
  auto texture = REGISTRY_GRAPHIC.GetTextureManager().GetTexture(name);
  if (!mTexture)
  {
    mTexture = std::get<0>(texture);
  }
  else if (mTexture != std::get<0>(texture))
  {
    // Текстуры должны совпадать.
    std::cout << "Block set texture error" << std::endl;
    return;
  }

  glm::vec4 pos = static_cast<glm::vec4>(std::get<1>(texture));// + 0.5f;
  
  glm::vec2 scale(1.0f / static_cast<glm::vec2>(mTexture->GetSize()));
  glm::vec4 coord(pos.x * scale.x, pos.y * scale.y, (pos.x + pos.z - 1) * scale.x, (pos.y + pos.w - 1) * scale.y);

  for (unsigned int i = 0; i < 6; ++i)
  {
    if (side & (1 << i))
    {
      mVertex[i * 4 + 0].texture = { coord.x, coord.y };
      mVertex[i * 4 + 1].texture = { coord.x, coord.w };
      mVertex[i * 4 + 2].texture = { coord.z, coord.w };
      mVertex[i * 4 + 3].texture = { coord.z, coord.y };
    }
  }
}

void Cube::FillBuffer(BufferArray<VertexVT> &buffer, const glm::vec3 &pos) const
{
  auto &vertex = buffer.Vertex();
  auto &index = buffer.Index();

  auto vertexIndex = vertex.size();
  vertex.insert(vertex.end(), mVertex.begin(), mVertex.end());
  for (unsigned int i = 0; i < 24; ++i)
  {
    vertex[vertexIndex + i].vertex += pos;
  }

  for (unsigned int i = 0; i < 36; ++i)
  {
    index.push_back(vertexIndex + mIndex[i]);
  }
}

void Cube::FillBuffer(BufferArray<VertexVT> &buffer, const glm::vec3 &pos, Side sides) const
{
  for (unsigned int i = 0; i < 6; ++i)
  {
    if (sides & (1 << i))
    {
      FillBufferSide(buffer, pos, i);
    }
  }
}

void Cube::FillBufferSide(BufferArray<VertexVT> &buffer, const glm::vec3 &pos, unsigned int side) const
{
  auto &vertex = buffer.Vertex();
  auto &index = buffer.Index();

  auto vertexIndex = vertex.size();
  vertex.insert(vertex.end(), &mVertex[side * 4], &mVertex[side * 4] + 4);
  for (unsigned int i = 0; i < 4; ++i)
  {
    vertex[vertexIndex + i].vertex += pos;
  }

  for (unsigned int i = 0; i < 6; ++i)
  {
    index.push_back(vertexIndex + indexCubeSide[i]);
  }
}

