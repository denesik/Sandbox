#include "SectorLoader.h"



SectorLoader::SectorLoader()
{
}


SectorLoader::~SectorLoader()
{
}

void SectorLoader::SetRadius(unsigned int radius)
{
  mRadius = radius;

  mSite.clear();

  int begin = -static_cast<int>(radius);
  int end = static_cast<int>(radius);
  glm::ivec3 pos(begin);
  for (; pos.z != end; ++pos.z)
  for (; pos.y != end; ++pos.y)
  for (; pos.x != end; ++pos.x)
  {
    mSite.push_back(pos);
  }
}

void SectorLoader::SetPos(const glm::ivec3 &pos)
{
  mPos = pos;

  // ��������� �� ���� ����������� �� ������ ������ �������� � ��������� ��.
  for (const auto &site : mSite)
  {

  }

  // ��������� ������ �������.
  for (const auto &site : mSite)
  {

  }
}
