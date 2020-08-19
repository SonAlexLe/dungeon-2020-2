#include "player.hpp"
#define MAX_X 25.f
#define MAX_Y 25.f // squared
#define ACCEL_RATE 30.f
#define ACCEL_RATE_NEG -ACCEL_RATE
#define DECCEL_RATE 20.f

//initial velocity is 0, default constructor
Player::Player(float x, float y, Room* room) : room_(room),
    velocity_(sf::Vector2f(0, 0)), Entity(x, y), 
    accDown_(false), accUp_(false), accLeft_(false), accRight_(false), reload_(0) {}

sf::Sprite& Player::GetSprite() { return sprite_; }

const std::string Player::GetSpriteName() const { return "player.png"; }

Room* Player::GetRoom() { return room_;}

void Player::SetRoom(Room* room) { room_ = room; }

void Player::SetHP(int hp) { hp_ = hp; }

int Player::GetHP() { return hp_; }

float Player::GetReload() { return reload_; }

//should be run at startup, maybe whenever a new player is initialized?
//same with other entities that have sprites
// void Player::load() {
//     sf::Texture texture_;
//     texture_.loadFromFile(GetSpriteName(), sf::IntRect(currPos_.x, currPos_.y, 10, 10));
//     sprite_.setTexture(texture_);
// }

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
        velocity_.y += std::min(ACCEL_RATE_NEG * dt.asSeconds(), MAX_Y - velocity_.y);
    }
    else{
        if(velocity_.y < 0){
            velocity_.y += DECCEL_RATE * dt.asSeconds();
        }
    }
    

    if(accLeft_){
        velocity_.x += std::min(ACCEL_RATE_NEG * dt.asSeconds(), MAX_X - velocity_.x);
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
    // updating the position
   currPos_ += 0.5f * dt.asSeconds() * (velocity_ + v0);
/* for now ignore mouse input
    for(auto i : mousebutts) {
        if(i.second) { // if a mouse button is pressed
            switch(i.first) {
                case sf::Mouse::Left:
                    projectile_.SetVelocity(this->velocity_ * 2.f);
                    //sets the projectile's position to the player's current position
                    if (projectile_.GetPosition().x == 0 && projectile_.GetPosition().y == 0)
                    projectile_.SetPosition(GetPosition());
                    break;
                default:
                    break;
            }
        } else { // if a mouse button is not pressed
            switch(i.first) {
                case sf::Mouse::Left:
                    break;
                default:
                    break;
            }
        }
    }
    */
    //also updates the projectile's position
    //projectile_.SetPosition(projectile_.GetPosition() + projectile_.GetVelocity());
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