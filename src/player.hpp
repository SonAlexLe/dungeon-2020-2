
#pragma once
#include "entity.hpp"
#include <map>

//placeholder, please include empty constructor for testing purposes

class Player : public Entity
{
public:

    Player();

    Player(double x, double y);

    void update(std::map<sf::Keyboard::Key, bool>& keys, std::map<sf::Mouse::Button, bool>& mousebutts, sf::Time dt);

private:

    sf::Vector2f velocity_;
};