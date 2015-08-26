#pragma once
#ifndef SectorLoader_h__
#define SectorLoader_h__

#include <glm/glm.hpp>
#include <vector>

class SectorLoader
{
public:
  SectorLoader();
  ~SectorLoader();

  void SetRadius(unsigned int radius);

  void SetPos(const glm::ivec3 &pos);

private:

  unsigned int mRadius = 0;

  glm::ivec3 mPos;

  std::vector<glm::ivec3> mSite;

};



#endif // SectorLoader_h__

