#ifndef __GAME_LEVEL_H__
#define __GAME_LEVEL_H__

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

class GameLevel {
 public:
  // level state
  std::vector<GameObject> cells;
  std::vector<std::vector<unsigned int>> cellData;

  // constructor
  GameLevel() {}
  // load level
  void Load(const char *file, unsigned int levelWidth, unsigned int levelHeight);
  // render level
  void Draw(SpriteRenderer &renderer);
  // update cellData
  void Conway();
  // initialize level
  void Init(unsigned int levelWidth, unsigned int levelHeight);
};

#endif