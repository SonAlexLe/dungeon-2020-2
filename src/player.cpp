#pragma once
#include "player.hpp"
#define MAX_X 25.f
#define MAX_Y 25.f // squared
#define ACCEL_RATE 2.f
#define ACCEL_RATE_NEG -ACCEL_RATE
#define DECCEL_RATE 1.f

Player::Player() {}

Player::Player(double x, double y) : Entity(x, y) {}

/**
 * Formulas used: (for each component of the vector)
 * v = v0 + at
 * dx = 1/2*t*(v+v0)
 */ 
void Player::update(std::map<sf::Keyboard::Key, bool>& keys, std::map<sf::Mouse::Button, bool>& mousebutts, sf::Time dt) {
    sf::Vector2f v0(velocity_);
    for(auto i : keys) {
        if (i.second) {
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
        } else {
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

    if (velocity_.y < -MAX_Y) velocity_.y = -MAX_Y;
    if (velocity_.x < -MAX_X) velocity_.x = -MAX_X;
    if (velocity_.y > MAX_Y) velocity_.y = MAX_Y;
    if (velocity_.x > MAX_X) velocity_.x = MAX_X;
    currPos_ += 0.5f * dt.asSeconds() * (velocity_ + v0);

    for(auto i : mousebutts) {
        if(i.second) {
            switch(i.first) {
                case sf::Mouse::Left:
                    break;
                case sf::Mouse::Right:
                    break;
                default:
                    break;
            }
        } else {
            switch(i.first) {
                case sf::Mouse::Left:
                    break;
                case sf::Mouse::Right:
                    break;
                default:
                    break;
            }
        }
    }
}