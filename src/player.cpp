#include "player.hpp"
#define MAX_X 50.f
#define MAX_Y 50.f
#define ACCEL_RATE 80.f
#define DECCEL_RATE 20.f
#define PLR_HP 30

Player::Player(std::shared_ptr<Room> room, sf::Texture& t)
    : Entity(room->GetWidth()/2,room->GetHeight()/2, sf::Vector2f(0,0)), room_(room),
    accDown_(false), accUp_(false), accLeft_(false), accRight_(false),
    reload_(0), hp_(PLR_HP), score_(0), immortal_(true), texture_(t)
{
    //load player sprite
    sprite_ = sf::Sprite(t, sf::IntRect(96,139,16,22));
    sprite_.setScale(sf::Vector2f(2, 2));
}

void Player::Draw(sf::RenderWindow* w, sf::Color c) {
    sf::FloatRect p_rec = sprite_.getGlobalBounds();
    sf::RectangleShape p_box(sf::Vector2f(p_rec.width, p_rec.height));
    //Boundary box for collision detection
    p_box.setOutlineThickness(2);
    p_box.setOutlineColor(c);
    p_box.setFillColor(sf::Color::Transparent);
    p_box.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(p_box);
    sprite_.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(sprite_);
}

//getter functions
sf::Sprite& Player::GetSprite() { return sprite_; }

void Player::SetRoom(std::shared_ptr<Room> r) { room_ = r; }

std::shared_ptr<Room> Player::GetRoom() { return room_; }

float Player::GetReload() {return reload_; }

/**
 * Formulas used: (for each component of the vector)
 * v = v0 + at
 * dx = 1/2*t*(v+v0)
 * acceleration/decceleration is constant
 * currently only LMB will fire a projectile
 */ 
void Player::update(sf::Time dt) {
    sf::Vector2f v0(velocity_);

    //check upwards acceleration, if not accelerating then decelerate until not moving up
    if(accUp_) {
        velocity_.y -= std::min(ACCEL_RATE * dt.asSeconds(), std::abs(-MAX_Y - velocity_.y));
    }
    else {
        if(velocity_.y < 0){
            velocity_.y += DECCEL_RATE * dt.asSeconds();
        }
    }
    
    //check left acceleration, if not accelerating then decelerate until not moving left
    if(accLeft_) {
        velocity_.x -= std::min(ACCEL_RATE * dt.asSeconds(), std::abs(-MAX_X - velocity_.x));
    }
    else {
        if(velocity_.x < 0){
            velocity_.x += DECCEL_RATE * dt.asSeconds();
        }
    }
    
    //check downwards acceleration, if not accelerating then decelerate until not moving down
    if(accDown_) {
        velocity_.y += std::min(ACCEL_RATE * dt.asSeconds(), MAX_Y - velocity_.y);
    }
    else{
        if(velocity_.y > 0){
            velocity_.y -= DECCEL_RATE * dt.asSeconds();
        }
    }

    //check right acceleration, if not accelerating then decelerate until not moving right
    if(accRight_) {
        velocity_.x += std::min(ACCEL_RATE * dt.asSeconds(), MAX_X - velocity_.x);
    }
    else {
        if(velocity_.x > 0){
            velocity_.x -= DECCEL_RATE * dt.asSeconds();
        }
    }
//track reload rate
    if(reload_ > 0) {
        reload_ -= std::min(dt.asSeconds(),reload_);
    }
//track invincibility frames
    if(immortal_ > 0) {
        immortal_ -= std::min(dt.asSeconds(),immortal_);
    }    


//move player up to speed
   currPos_ += 0.5f * dt.asSeconds() * (velocity_ + v0);

//make sure the player stays within the play area.
    if(currPos_.x < 0) { currPos_.x = 0; velocity_.x = 0; }
    if(currPos_.y < 0) { currPos_.y = 0; velocity_.y = 0; }
    auto bounds = sprite_.getGlobalBounds();
    if (currPos_.x+bounds.width/3 > GetRoom()->GetWidth()) {
        currPos_ = sf::Vector2f(GetRoom()->GetWidth()-bounds.width/3, currPos_.y);
        velocity_.x = 0;
    }
    if (currPos_.y+bounds.height/3 > GetRoom()->GetHeight()) {
        currPos_ = sf::Vector2f(currPos_.x, GetRoom()->GetHeight()-bounds.height/3);
        velocity_.y = 0;
    }
}

void Player::Attack() 
{
    //set the player reload time
    reload_ = 0.5;
}

//input handling methods
void Player::accUp(bool isdown) { accUp_ = isdown; }
void Player::accLeft(bool isdown) { accLeft_ = isdown; }
void Player::accDown(bool isdown) { accDown_ = isdown; }
void Player::accRight(bool isdown) { accRight_ = isdown; }