#pragma once
#ifndef Atlas_h__
#define Atlas_h__

#include "Bitmap.h"
#include <glm\glm.hpp>
#include <map>
#include <functional>

class Atlas
{
public:
  Atlas(const glm::uvec2 &size);
  ~Atlas();

  bool Add(const Bitmap &bitmap);

  const Bitmap &Get() const;

private:
  Bitmap mBitmap;

  struct Node
  {
    Node *right = nullptr;
    Node *bottom = nullptr;
    glm::uvec2 pos;
    glm::uvec2 size;
    Node(const glm::uvec2 &p, const glm::uvec2 &s)
      : pos(p), size(s)
    {
    }
    ~Node()
    {
      if (right)
      {
        delete right;
      }
      if (bottom)
      {
        delete bottom;
      }
    }
  } mRoot;

  std::multimap<glm::uvec2, Node *, std::function<bool(const glm::uvec2 &, const glm::uvec2 &)>> mNodes;

private:

  

};



#endif // Atlas_h__
