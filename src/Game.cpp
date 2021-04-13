#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

// Game-related State data
SpriteRenderer* renderer;

Game::Game(unsigned int _width, unsigned int _height) : state(GAME_ACTIVE), keys(), width(_width), height(_height) {}

Game::~Game() { delete renderer; }

void Game::Init() {
  // load shaders
  ResourceManager::LoadShader("../src/shaders/sprite.vs", "../src/shaders/sprite.fs", nullptr, "sprite");
  // configure shaders
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
  ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
  // set render-specific controls
  renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
  // load texture
  ResourceManager::LoadTexture2D("../src/textures/cell.png", true, "cell");
  GameLevel level;
  level.Load("../src/levels/seed.lvl", this->width, this->height);
  this->level = level;
}

void Game::ProcessInput(float deltaTime) {}

void Game::Update(float deltaTime) {
  this->level.Conway();
  this->level.Init(this->width, this->height);
}

void Game::Render() {
  if (this->state == GAME_ACTIVE) {
    this->level.Draw(*renderer);
  }
}
