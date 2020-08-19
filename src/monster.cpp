#include "monster.hpp"
#include <iostream>
#define SPEED 20

Monster::Monster(Room* room, int hp) : room_(room), hp_(hp),
    Entity(room->GetWidth(), room->GetHeight(), sf::Vector2f(0, 0)) {}

const std::string Monster::GetSpriteName() const { return "monster.png"; }

void Monster::load() {
    sf::Texture texture_;
    texture_.loadFromFile(GetSpriteName(), sf::IntRect(currPos_.x, currPos_.y, SPEED, SPEED));
    sprite_.setTexture(texture_);
}

int Monster::GetHP() { return hp_; }

void Monster::SetHP(int hp) { hp_ = hp; }