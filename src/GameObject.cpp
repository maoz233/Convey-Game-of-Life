#include "GameObject.h"

GameObject::GameObject() : position(0.0f, 0.0f), size(1.0f, 1.0f), color(glm::vec3(0.0f, 1.0f, 0.0f)), sprite() {}
GameObject::GameObject(glm::vec2 _position, glm::vec2 _size, Texture2D _sprite, glm::vec3 _color)
    : position(_position), size(_size), color(_color), sprite(_sprite) {}

void GameObject::Draw(SpriteRenderer &renderer) {
  renderer.DrawSprite(this->sprite, this->position, this->size, 0.0f, this->color);
}