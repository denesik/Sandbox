#include "RenderSector.h"



RenderSector::RenderSector()
{
  mBufferStatic.EnableAttribute(ATTRIBUTE_VERTEX, 3, offsetof(VertexVT, vertex));
  mBufferStatic.EnableAttribute(ATTRIBUTE_TEXTURE, 2, offsetof(VertexVT, texture));

  memset(mMap, 0, SECTOR_SIZE * SECTOR_SIZE * SECTOR_SIZE);
  for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
  for (unsigned int x = 0; x < SECTOR_SIZE; ++x)
  {
    mMap[z][0][x] = 1;
  }
}


RenderSector::~RenderSector()
{
}

void RenderSector::Generate()
{
  auto &vertex = mBufferStatic.Vertex();
  auto &index = mBufferStatic.Index();

  vertex.clear();
  index.clear();

  Cube cube;

  for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
  for (unsigned int y = 0; y < SECTOR_SIZE; ++y)
  for (unsigned int x = 0; x < SECTOR_SIZE; ++x)
  {
    if (mMap[z][y][x])
    {
      unsigned int vertexIndex = vertex.size();
      for (unsigned int i = 0; i < cube.mVertex.size(); ++i)
      {
        vertex.push_back(
        {
          {
            cube.mVertex[i].vertex.x + x,
            cube.mVertex[i].vertex.y + y,
            cube.mVertex[i].vertex.z + z
          } ,
          cube.mVertex[i].texture
        });
      }
      for (unsigned int i = 0; i < cube.mIndex.size(); ++i)
      {
        index.push_back(vertexIndex + cube.mIndex[i]);
      }
    }
  }
}
