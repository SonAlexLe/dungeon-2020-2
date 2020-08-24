#include "monster.hpp"

Monster::Monster() {}

const std::string Monster::GetSpriteName() const { return "monster.png"; }

void Monster::load() {
    sf::Texture texture_;
    texture_.loadFromFile(GetSpriteName(), sf::IntRect(currPos_.x, currPos_.y, 10, 10));
    sprite_.setTexture(texture_);
}

void Monster::update(sf::Time dt) {
    currPos_ += velocity_;
}