#include "orc.hpp"
#define ORC_HP 100
#define SPEED 20

Orc::Orc(Room* room) : Monster(room, ORC_HP) {}

void Orc::update(sf::Time dt) {
    if(currPos_.x >= room_->GetWidth() && currPos_.y >= room_->GetHeight())
        velocity_ = sf::Vector2f(-SPEED, -SPEED);
    if(currPos_.x < 0 && currPos_.y < 0) {
        velocity_ = sf::Vector2f(SPEED, SPEED);
    }
    currPos_ += dt.asSeconds() * velocity_;
}