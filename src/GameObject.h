#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Texture.h"
#include "SpriteRenderer.h"

class GameObject {
 public:
  // object state
  glm::vec2 position, size;
  glm::vec3 color;

  // render state
  Texture2D sprite;

  // constructor
  GameObject();
  GameObject(glm::vec2 _position, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color = glm::vec3(0.0f, 1.0f, 0.0f));
  // draw sprite
  virtual void Draw(SpriteRenderer &renderer);
};

#endif