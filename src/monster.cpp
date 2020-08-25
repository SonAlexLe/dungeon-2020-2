#include "monster.hpp"
#define ORC_SPEED 30.f
#define ORC_HP 200

Monster::Monster() {}

Monster::Monster(float x, float y, sf::Vector2f velocity, int hp, Player* p)
    : Entity(x, y, velocity), hp_(hp), p_(p) {}

const std::string Monster::GetSpriteName() const { return "monster.png"; }

void Monster::load() {
    sf::Texture texture_;
    texture_.loadFromFile(GetSpriteName(), sf::IntRect(currPos_.x, currPos_.y, 10, 10));
    sprite_.setTexture(texture_);
}

void Monster::SetHP(int hp) { hp_ = hp; }

int Monster::GetHP() { return hp_; }

void Monster::SetPlayer(Player* p) { p_ = p; }

Player* Monster::GetPlayer() { return p_; }

Orc::Orc(float x, float y, Player* p)
    : Monster(x, y, sf::Vector2f(ORC_SPEED, ORC_SPEED), ORC_HP, p) {}

void Orc::update(sf::Time dt) {
    if(currPos_.x >= p_->GetRoom()->GetWidth() && currPos_.y >= p_->GetRoom()->GetHeight())
        velocity_ = sf::Vector2f(-ORC_SPEED, -ORC_SPEED);
    if(currPos_.x < 0 && currPos_.y < 0) {
        velocity_ = sf::Vector2f(ORC_SPEED, ORC_SPEED);
    }
    currPos_ += dt.asSeconds() * velocity_;
}