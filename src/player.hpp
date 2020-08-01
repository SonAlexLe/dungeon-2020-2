#pragma once
#include "entity.hpp"
#include <vector>

//placeholder, please include empty constructor for testing purposes

class Player : public Entity
{
public:
    Player();
    Player(double x, double y);
    void update(sf::Time df, std::vector<sf::Event::KeyEvent> keys = std::vector<sf::Event::KeyEvent>(), bool isPressed = false);
private:
    int a_;
};