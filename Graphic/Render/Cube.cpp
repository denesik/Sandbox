#include "Cube.h"


#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include "TextureManager.h"
#include <algorithm>

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
  : mTextures(6)
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

  TextureManager textureManager;
  textureManager.LoadTexture("Graphic/Textures/tmp2.png");
  mTexture = std::get<0>(textureManager.GetTexture("Graphic/Textures/tmp2.png"));
}


Cube::~Cube()
{
}

void Cube::SetTexture(Side side, const std::string &name)
{
  std::shared_ptr<Bitmap> bitmap = std::make_shared<Bitmap>(name);

  unsigned int s = 1;
  for (unsigned int i = 0; i < 6; ++i)
  {
    if (side & (s << i))
    {
      mTextures[i] = bitmap;
    }
  }
}

void Cube::Compile()
{
  auto textures = mTextures;
  std::sort(textures.begin(), textures.end());
  unsigned int count = 0;
  for (unsigned int i = 0; i < 5; i++)
  {
    if (textures[i] != textures[i + 1])
    {
      ++count;
    }
  }
}

