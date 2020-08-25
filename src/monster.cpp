#include "monster.hpp"
#define ORC_SPEED 30.f
#define ORGE_SPEED 10.f
#define ORC_HP 200
#define ORGE_HP 100

Monster::Monster(float x, float y, Room* room, sf::Vector2f velocity, int hp)
    : velocity_(velocity), hp_(hp), Entity(x, y, room) {}

Monster::Monster(float x, float y, sf::Vector2f velocity, int hp, Player* p)
    : Entity(x, y, velocity), hp_(hp), p_(p) {}

const std::string Monster::GetSpriteName() const { return "monster.png"; }

void Monster::SetHP(int hp) { hp_ = hp; }

int Monster::GetHP() { return hp_; }

void Monster::SetPlayer(Player* p) { p_ = p; }

Player* Monster::GetPlayer() { return p_; }

sf::Sprite& Monster::GetSprite() { return sprite_; }

Orc::Orc(float x, float y, Player* p)
    : Monster(x, y, sf::Vector2f(ORC_SPEED, ORC_SPEED), ORC_HP, p)
{
    if (!texture_.loadFromFile("src/Sprites/orc.png")) std::cout << "sprite error" << std::endl;
    sprite_.setTexture(texture_);
    sprite_.setScale(sf::Vector2f(0.08f, 0.08f));
}

void Orc::update(sf::Time dt) {
    if(currPos_.x >= p_->GetRoom()->GetWidth() && currPos_.y >= p_->GetRoom()->GetHeight())
        velocity_ = sf::Vector2f(-ORC_SPEED, -ORC_SPEED);
    if(currPos_.x < 0 && currPos_.y < 0) {
        velocity_ = sf::Vector2f(ORC_SPEED, ORC_SPEED);
    }
    currPos_ += dt.asSeconds() * velocity_;
}

Orge::Orge(float x, float y, Player* p)
    : Monster(x, y, sf::Vector2f(0, 0), ORGE_HP, p)
{
    if (!texture_.loadFromFile("src/Sprites/orge.png")) std::cout << "sprite error" << std::endl;
    sprite_.setTexture(texture_);
    sprite_.setScale(sf::Vector2f(0.05f, 0.05f));
}

int Monster::GetHP() { return hp_; }

void Monster::SetHP(int hp) { hp_ = hp; }

Orc::Orc(float x, float y, Room* room) :
    Monster(x, y, room, sf::Vector2f(ORC_SPEED, ORC_SPEED), ORC_HP) {}

void Orc::update(sf::Time dt) {
    if(currPos_.x >= room_->GetWidth() && currPos_.y >= room_->GetHeight())
        velocity_ = sf::Vector2f(-ORC_SPEED, -ORC_SPEED);
    if(currPos_.x < 0 && currPos_.y < 0) {
        velocity_ = sf::Vector2f(ORC_SPEED, ORC_SPEED);
    }
    currPos_ += dt.asSeconds() * velocity_;
}

Werewolf::Werewolf(float x, float y, Room* room) :
    Monster(x, y, room, sf::Vector2f(0, 0), WEREWOLF_HP) {}

void Werewolf::update(sf::Time dt) {
    sf::Vector2f target = room_->GetPlayer()->GetPosition();
    sf::Vector2f diff = target - currPos_;
    diff = diff/(float)sqrt(diff.x*diff.x + diff.y*diff.y);
    velocity_ = diff * WEREWOLF_SPEED;
    currPos_ += dt.asSeconds() * velocity_;
}