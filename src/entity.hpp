#pragma once
#include <SFML/System.hpp>

class Entity
{
public:
    Entity();
    Entity(double x, double y);
    virtual ~Entity();
//todo: make update virtual
    virtual void update(sf::Time dt);
private:
    //consider using the specialized form sf::Vector2f -L
    sf::Vector2f velocity_;
    sf::Vector2f currPos_;
};