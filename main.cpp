// ============================================================================
// ==                   Copyright (c) 2015, Smirnov Denis                    ==
// ==                  See license.txt for more information                  ==
// ============================================================================
#include "Game.h"
#include <stdlib.h>
#include <time.h>


int main()
{
  srand(static_cast<unsigned int>(time(0)));

  Game game;
  return game.Run();
}
