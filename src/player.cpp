#pragma once
#include "player.hpp"
//todo: player needs to be able to move around (and must have a 2d location)
//inherits from Creature
Player::Player() {}

Player::Player(double x, double y) : Entity(x, y) {}

/**
 * should update have any other params?
 * How do these cases work exactly? turn the player in 1 of the 4 compass directions?
 * i think acceleration should be ignored for now
 * can the player move in any of the 360deg directions? or only 4 compass directions?
*/
void Player::update(sf::Time df, std::vector<sf::Event::KeyEvent> keys, bool isPressed) {
    for(auto i : keys) {
        switch(i.code) {
            case sf::Keyboard::W:
                break;
            case sf::Keyboard::A:
                break;
            case sf::Keyboard::S:
                break;
            case sf::Keyboard::D:
                break;
        }
    }
}