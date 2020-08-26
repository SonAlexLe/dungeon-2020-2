#include "monster.hpp"
#define ORC_SPEED 15.f
#define ORGE_SPEED 10.f
#define ORC_HP 5
#define ORGE_HP 10

Monster::Monster() {}

Monster::Monster(float x, float y, sf::Vector2f velocity, int hp, Player* p)
    : Entity(x, y, velocity), hp_(hp), p_(p) {}

const std::string Monster::GetSpriteName() const { return "monster.png"; }

void Monster::Draw(sf::RenderWindow* w) {
    sf::FloatRect m_rec = sprite_.getGlobalBounds();
    sf::RectangleShape m_box(sf::Vector2f(m_rec.width, m_rec.height));
    m_box.setOutlineThickness(2);
    m_box.setOutlineColor(sf::Color::Transparent);
    m_box.setFillColor(sf::Color::Transparent);
    m_box.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(m_box);
    sprite_.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(sprite_);
}

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
    if (!sprite_.getGlobalBounds().intersects(p_->GetSprite().getGlobalBounds())) {
        if(currPos_.x >= p_->GetRoom()->GetWidth() && currPos_.y >= p_->GetRoom()->GetHeight())
            velocity_ = sf::Vector2f(-ORC_SPEED, -ORC_SPEED);
        else if(currPos_.x < 0 && currPos_.y < 0)
            velocity_ = sf::Vector2f(ORC_SPEED, ORC_SPEED);
        currPos_ += dt.asSeconds() * velocity_;
    } else {
        hp_--;
        p_->SetHP(p_->GetHP()-1);
    }
}

Orge::Orge(float x, float y, Player* p)
    : Monster(x, y, sf::Vector2f(0, 0), ORGE_HP, p)
{
    if (!texture_.loadFromFile("src/Sprites/orge.png")) std::cout << "sprite error" << std::endl;
    sprite_.setTexture(texture_);
    sprite_.setScale(sf::Vector2f(0.05f, 0.05f));
}

void Orge::update(sf::Time dt) {
    if (sprite_.getGlobalBounds().intersects(p_->GetSprite().getGlobalBounds())) {
        hp_--;
        p_->SetHP(p_->GetHP()-3);
        velocity_ = sf::Vector2f(0.f, 0.f);
    } else {
        sf::Vector2f target = p_->GetPosition();
        sf::Vector2f diff = target - currPos_;
        diff = diff/(float)sqrt(diff.x*diff.x + diff.y*diff.y);
        velocity_ = diff * ORGE_SPEED;
    }
    currPos_ += dt.asSeconds() * velocity_;
}