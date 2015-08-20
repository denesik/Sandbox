#include "RenderSector.h"



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

  vertex.clear();
  index.clear();



  const auto &map = mSector.mMap;

  for (unsigned int z = 0; z < SECTOR_SIZE; ++z)
  for (unsigned int y = 0; y < SECTOR_SIZE; ++y)
  for (unsigned int x = 0; x < SECTOR_SIZE; ++x)
  {
    if (map[z][y][x] > 0)
    {
      const Model &model = map[z][y][x]->GetModel();
      
      unsigned int vertexIndex = vertex.size();
      for (unsigned int i = 0; i < model.GetVertex().size(); ++i)
      {
        vertex.push_back(
        {
          {
            model.GetVertex()[i].vertex.x + x,
            model.GetVertex()[i].vertex.y + y,
            model.GetVertex()[i].vertex.z + z
          } ,
          model.GetVertex()[i].texture
        });
      }
      for (unsigned int i = 0; i < model.GetIndex().size(); ++i)
      {
        index.push_back(vertexIndex + model.GetIndex()[i]);
      }
    }
  }

  mBufferStatic.Compile();
}

BufferArray<VertexVT> & RenderSector::GetBuffer()
{
  return mBufferStatic;
}
