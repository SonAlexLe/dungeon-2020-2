#pragma once

class Entity
{
public:
    Entity::Entity(double x, double y) : currPos_(x, y) {}
    virtual ~Entity();

    void update(sf::Time dt);

private:
    sf::Vector2<double> velocity_;
    sf::Vector2<double> currPos_;
};