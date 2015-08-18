#include "Game.h"
#include <stdlib.h>
#include <time.h>

class A
{
  int k = 1;
  char b = 2;
  float f = 3;
};

class B : public A
{
  char t = 4;
  char c = 5;
};

enum 
{
  sizeA = sizeof( A), // 12
  sizeB = sizeof( B), // 16
};

int main()
{
  srand(static_cast<unsigned int>(time(0)));

  Game game;
  return game.Run();
}
