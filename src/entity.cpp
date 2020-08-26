#include "entity.hpp"

//Virtual class that is inherited by all creatures within the dungeon.

Entity::Entity() {}

Entity::~Entity() {}

Entity::Entity(float x, float y, sf::Vector2f velocity) : currPos_(x, y) , velocity_(velocity){}

//default update method, simply keeps an object in constant movement.
void Entity::update(sf::Time dt) {
    currPos_ += velocity_ * dt.asSeconds();
}

sf::Vector2f& Entity::GetVelocity() { return velocity_; }
sf::Vector2f& Entity::GetPosition() { return currPos_; }

void Entity::SetPosition(sf::Vector2f pos) { currPos_ = pos; }
