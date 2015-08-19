#include "RenderSector.h"



RenderSector::RenderSector()
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

  vertex.clear();
  index.clear();

  Cube cube1;
  cube1.SetTexture(Cube::ALL, "Graphic/Textures/tmp2.png");
  Cube cube2;
  cube2.SetTexture(Cube::ALL, "Graphic/Textures/tmp.png");

  const auto &map = mMap.mMap;

  for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
  for (unsigned int y = 0; y < SECTOR_SIZE; ++y)
  for (unsigned int x = 0; x < SECTOR_SIZE; ++x)
  {
    if (map[z][y][x] > 0)
    {
      Cube &cube = map[z][y][x] == 1 ? cube1 : cube2;
      
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
