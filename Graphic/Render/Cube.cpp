#include "Cube.h"


#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>

// static glm::vec3 vertexCubeLBF(-0.5f, -0.5f, 0.5f);
// static glm::vec3 vertexCubeLTF(-0.5f, 0.5f, 0.5f);
// static glm::vec3 vertexCubeRBF(0.5f, -0.5f, 0.5f);
// static glm::vec3 vertexCubeRTF(0.5f, 0.5f, 0.5f);
// static glm::vec3 vertexCubeLBB(-0.5f, -0.5f, -0.5f);
// static glm::vec3 vertexCubeLTB(-0.5f, 0.5f, -0.5f);
// static glm::vec3 vertexCubeRBB(0.5f, -0.5f, -0.5f);
// static glm::vec3 vertexCubeRTB(0.5f, 0.5f, -0.5f);
// 
// static glm::vec3 vertexCube[] =
// {
//   vertexCubeLBF,vertexCubeLTF,vertexCubeRTF,vertexCubeRBF, // front
//   vertexCubeRBF,vertexCubeRTF,vertexCubeRTB,vertexCubeRBB, // right
//   vertexCubeRBB,vertexCubeRTB,vertexCubeLTB,vertexCubeLBB, // back
//   vertexCubeLBB,vertexCubeLTB,vertexCubeLTF,vertexCubeLBF, // left
//   vertexCubeLTF,vertexCubeLTB,vertexCubeRTB,vertexCubeRTF, // top
//   vertexCubeLBB,vertexCubeLBF,vertexCubeRBF,vertexCubeRBB  // bot
// };

static float vertexCube[][3] =
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

static float textureCube[][2] =
{
  { 0.0f, 0.0f },{ 0.0f, 1.0f },{ 1.0f, 1.0f },{ 1.0f, 0.0f }
};

Cube::Cube()
{
}


Cube::~Cube()
{
}

void Cube::TestDraw()
{
  glBindVertexArray(mVao);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
}

void Cube::TestCompile()
{
  std::vector<unsigned int> index;
  for (unsigned int i = 0; i < 6; ++i)
  {
    for (unsigned int j = 0; j < 6; ++j)
    {
      index.push_back(i * 4 + indexCubeSide[j]);
    }
  }

  std::vector<float> textureCoord;
  for (unsigned int i = 0; i < 6; ++i)
  {
    for (unsigned int j = 0; j < 4; ++j)
    {
      for (unsigned int k = 0; k < 2; ++k)
      {
        textureCoord.push_back(textureCube[j][k]);
      }
    }
  }


  glGenVertexArrays(1, &mVao);
  glBindVertexArray(mVao);

  unsigned int vbo = 0;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24 * 3, vertexCube, GL_STATIC_DRAW);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

//   unsigned int tbo = 0;
//   glGenBuffers(1, &tbo);
//   glBindBuffer(GL_ARRAY_BUFFER, tbo);
//   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24 * 2, &textureCoord[0], GL_STATIC_DRAW);
//   glEnableVertexAttribArray(1);
//   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  unsigned int vbi = 0;
  glGenBuffers(1, &vbi);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbi);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index.size(), &index[0], GL_STATIC_DRAW);
  
}
