#pragma once
#include "player.hpp"
#define MAX_X 25.f
#define MAX_Y 25.f // squared
#define ACCEL_RATE 2.f
#define ACCEL_RATE_NEG -ACCEL_RATE
#define DECCEL_RATE 1.f

//initial velocity is 0, default constructor
//TODO: change intitial position of projectile is 0, 0
Player::Player() {
    projectile_ = Projectile(0, 0, "projectile", 1, this, 10);
    velocity_ = sf::Vector2f(0, 0);
}

Player::Player(float x, float y) : Entity(x, y) { velocity_ = sf::Vector2f(0, 0); }

sf::Sprite& Player::GetSprite() { return sprite_; }

const std::string Player::GetSpriteName() { return "player.png"; }

//should be run at startup, maybe whenever a new player is initialized?
//same with other entities that have sprites
void Player::load() {
    sf::Texture texture_;
    texture_.loadFromFile(GetSpriteName(), sf::IntRect(currPos_.x, currPos_.y, 10, 10));
    sprite_.setTexture(texture_);
}

/**
 * Formulas used: (for each component of the vector)
 * v = v0 + at
 * dx = 1/2*t*(v+v0)
 * acceleration/decceleration is constant
 * currently only LMB will fire a projectile
 * for now, the velocity of the projectile is two times the player's
 */ 
void Player::update(std::map<sf::Keyboard::Key, bool>& keys, std::map<sf::Mouse::Button, bool>& mousebutts, sf::Time dt) {
    sf::Vector2f v0(velocity_);
    for(auto i : keys) {
        if (i.second) { // speeding up if a key is pressed
            switch(i.first) {
                case sf::Keyboard::W:
                    velocity_.y += ACCEL_RATE_NEG * dt.asSeconds();
                    break;
                case sf::Keyboard::A:
                    velocity_.x += ACCEL_RATE_NEG * dt.asSeconds();
                    break;
                case sf::Keyboard::S:
                    velocity_.y += ACCEL_RATE * dt.asSeconds();
                    break;
                case sf::Keyboard::D:
                    velocity_.x += ACCEL_RATE * dt.asSeconds();
                    break;
                default:
                    break;
            }
        } else { // slowing down if a key is not pressed
            switch(i.first) {
                case sf::Keyboard::W:
                    if (velocity_.y > -MAX_Y) velocity_.y += ACCEL_RATE_NEG * dt.asSeconds();
                    else velocity_.y = -MAX_Y;
                    break;
                case sf::Keyboard::A:
                    if (velocity_.x > -MAX_X) velocity_.x += ACCEL_RATE_NEG * dt.asSeconds();
                    else velocity_.x = -MAX_X;
                    break;
                case sf::Keyboard::S:
                    if (velocity_.y < MAX_Y) velocity_.y += ACCEL_RATE * dt.asSeconds();
                    else velocity_.y = MAX_Y;
                    break;
                case sf::Keyboard::D:
                    if (velocity_.x < MAX_X) velocity_.x += ACCEL_RATE * dt.asSeconds();
                    else velocity_.x = MAX_X;
                    break;
                default:
                    break;
            }
        }
    }
    // velocity cannot be too high
    if (velocity_.y < -MAX_Y) velocity_.y = -MAX_Y;
    if (velocity_.x < -MAX_X) velocity_.x = -MAX_X;
    if (velocity_.y > MAX_Y) velocity_.y = MAX_Y;
    if (velocity_.x > MAX_X) velocity_.x = MAX_X;
    // updating the position
    currPos_ += 0.5f * dt.asSeconds() * (velocity_ + v0);

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
    //also updates the projectile's position
    projectile_.SetPosition(projectile_.GetPosition() + projectile_.GetVelocity());
}