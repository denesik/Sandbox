// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Game.h"
#include <stdlib.h>
#include <time.h>

#include "Graphic/Render/Vertex.h"

int main()
{
  srand(static_cast<unsigned int>(time(0)));

  VertexVTN v;

  v.color = {};
  v.mAttributeInfo[0];

  Game game;
  return game.Run();
}
