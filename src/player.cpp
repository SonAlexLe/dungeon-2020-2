#include "player.hpp"
#define MAX_X 50.f
#define MAX_Y 50.f
#define ACCEL_RATE 80.f
#define ACCEL_RATE_NEG -ACCEL_RATE
#define DECCEL_RATE 20.f
#define PLR_HP 10

Player::Player(Room* room) : room_(room), Entity(room->GetWidth()/2,room->GetHeight()/2, sf::Vector2f(0,0)), 
accDown_(false), accUp_(false), accLeft_(false), accRight_(false), reload_(0), hp_(PLR_HP), score_(0)
{
    //load player texture
    if (!texture_.loadFromFile("src/Sprites/game_texture.png")) std::cout << "sprite error" << std::endl;
    sprite_ = sf::Sprite(texture_,sf::IntRect(96,139,16,32));
    //sprite_.setTexture(texture_);
    sprite_.setScale(sf::Vector2f(2, 2));
}

void Player::Draw(sf::RenderWindow* w) {
    sf::FloatRect p_rec = sprite_.getGlobalBounds();
    sf::RectangleShape p_box(sf::Vector2f(p_rec.width, p_rec.height));
    //Boundary box for collision detection
    p_box.setOutlineThickness(2);
    p_box.setOutlineColor(sf::Color::Transparent);
    p_box.setFillColor(sf::Color::Transparent);
    p_box.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(p_box);
    sprite_.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(sprite_);
}

//getter functions
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
        if(reload_ == 0) {std::cout << "LOADED" << std::endl;}
    }

//move player up to speed
   currPos_ += 0.5f * dt.asSeconds() * (velocity_ + v0);

//make sure the player stays within the play area.
   if(currPos_.x < 0) { currPos_.x = 0; velocity_.x = 0; }
   if(currPos_.x > room_->GetWidth()) { currPos_.x = room_->GetWidth(); velocity_.x = 0; }
   if(currPos_.y < 0) { currPos_.y = 0; velocity_.y = 0; }
   if(currPos_.y > room_->GetHeight()) { currPos_.y = room_->GetHeight(); velocity_.y = 0; }
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