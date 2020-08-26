#include "player.hpp"
#define MAX_X 25.f
#define MAX_Y 25.f // squared
#define ACCEL_RATE 30.f
#define ACCEL_RATE_NEG -ACCEL_RATE
#define DECCEL_RATE 20.f
#define PLR_HP 500

//initial velocity is 0, default constructor
//TODO: change intitial position of projectile is 0, 0
/*Player::Player() {
    projectile_ = Projectile(0, 0, "projectile", 1, this, 10);
    velocity_ = sf::Vector2f(0, 0);
}
*/
Player::Player(Room* room) : room_(room), Entity(room->GetWidth()/2,room->GetHeight()/2, sf::Vector2f(0,0)), 
accDown_(false), accUp_(false), accLeft_(false), accRight_(false), reload_(0), hp_(PLR_HP)
{
    if (!texture_.loadFromFile("src/Sprites/player.png")) std::cout << "sprite error" << std::endl;
    sprite_.setTexture(texture_);
    sprite_.setScale(sf::Vector2f(0.1f, 0.1f));
}

void Player::Draw(sf::RenderWindow* w) {
    sf::FloatRect p_rec = sprite_.getGlobalBounds();
    sf::RectangleShape p_box(sf::Vector2f(p_rec.width, p_rec.height));
    p_box.setOutlineThickness(2);
    p_box.setOutlineColor(sf::Color::Red);
    p_box.setFillColor(sf::Color::Transparent);
    p_box.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(p_box);
    sprite_.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(sprite_);
}

sf::Sprite& Player::GetSprite() { return sprite_; }

const std::string Player::GetSpriteName() const { return "src/Sprites/player.png"; }

Room *Player::GetRoom() { return room_; } 

void Player::SetRoom(Room* r) { room_ = r; }

float Player::GetReload() {return reload_;}



/**
 * Formulas used: (for each component of the vector)
 * v = v0 + at
 * dx = 1/2*t*(v+v0)
 * acceleration/decceleration is constant
 * currently only LMB will fire a projectile
 * for now, the velocity of the projectile is two times the player's
 */ 
void Player::update(sf::Time dt) {
    sf::Vector2f v0(velocity_);
    if(DEBUGGING){
        std::cout << v0.x << " : " << v0.y << std::endl;
    }
    if(accUp_){
        velocity_.y -= std::min(ACCEL_RATE * dt.asSeconds(), std::abs(-MAX_Y - velocity_.y));
    }
    else{
        if(velocity_.y < 0){
            velocity_.y += DECCEL_RATE * dt.asSeconds();
        }
    }
    

    if(accLeft_){
        velocity_.x -= std::min(ACCEL_RATE * dt.asSeconds(), std::abs(-MAX_X - velocity_.x));
    }
    else{
        if(velocity_.x < 0){
            velocity_.x += DECCEL_RATE * dt.asSeconds();
        }
    }
    

    if(accDown_){
        velocity_.y += std::min(ACCEL_RATE * dt.asSeconds(), MAX_Y - velocity_.y);
    }
    else{
        if(velocity_.y > 0){
            velocity_.y -= DECCEL_RATE * dt.asSeconds();
        }
    }
    if(accRight_){
        velocity_.x += std::min(ACCEL_RATE * dt.asSeconds(), MAX_X - velocity_.x);
    }
    else{
        if(velocity_.x > 0){
            velocity_.x -= DECCEL_RATE * dt.asSeconds();
        }
    }
//track reload rate
    if(reload_ > 0) {
        reload_ -= std::min(dt.asSeconds(),reload_);
    }
   currPos_ += 0.5f * dt.asSeconds() * (velocity_ + v0);
    if(DEBUGGING){
        std::cout << accUp_<< " " <<accDown_<<" " << accLeft_<<" "<<accRight_<<" "<< std::endl;
    }
}

void Player::Attack() 
{
    reload_ = 1;
}

//input handling methods, by Leo
void Player::accUp(bool isdown)
{
    accUp_ = isdown;
}
void Player::accLeft(bool isdown)
{
    accLeft_ = isdown;
}
void Player::accDown(bool isdown)
{
    accDown_ = isdown;
}
void Player::accRight(bool isdown)
{
    accRight_ = isdown;
}