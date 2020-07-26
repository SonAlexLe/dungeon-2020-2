#pragma once
#include <SFML/System.hpp>

class Entity
{
public:
    Entity(double x, double y) : currPos_(x, y) {}
    virtual ~Entity();
//todo: make update virtual
    void update(sf::Time dt);

private:
    sf::Vector2<double> velocity_;
    sf::Vector2<double> currPos_;
};