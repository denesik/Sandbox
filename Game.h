#ifndef GAME_H
#define GAME_H

class Game
{
public:
  Game();
  ~Game();

  int Run();

  void Initialize();

  void Update();

  void Draw();

private:

  bool Initialized = false;

};

#endif // GAME_H
