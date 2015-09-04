// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#pragma once
#ifndef Vertex_h__
#define Vertex_h__

#include <glm/glm.hpp>
#include <array>
#include "VertexTools.h"

enum AttributeType
{
  ATTRIBUTE_UNKNOWN = 0,
  ATTRIBUTE_VERTEX = 1,
  ATTRIBUTE_COLOR = 2,
  ATTRIBUTE_TEXTURE = 3,
  ATTRIBUTE_NORMAL = 4,
};

struct Attribute
{
  unsigned int type;
  unsigned int size;
  unsigned int offset;
};


VERTEX
(
  (VertexVTN)
  (glm::vec3, vertex, ATTRIBUTE_VERTEX)
  (glm::vec2, texture, ATTRIBUTE_TEXTURE)
  (glm::vec3, normal, ATTRIBUTE_NORMAL)
  (glm::vec3, color, ATTRIBUTE_COLOR)
)



#endif // Vertex_h__

