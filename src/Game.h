#ifndef __GAME_H__
#define __GAME_H__

#include "GameLevel.h"

enum GameState { GAME_ACTIVE, GAME_PAUSE, GAME_TERMINATE };

class Game {
 public:
  // game state
  GameState state;
  bool keys[1024];
  unsigned int width, height;
  // game level
  GameLevel level;

  // constructor
  Game(unsigned int _width, unsigned int _height);
  // destructor
  ~Game();
  // initialize
  void Init();
  // game loop
  void ProcessInput(float deltaTime);
  void Update(float deltaTime);
  void Render();
};

#endif