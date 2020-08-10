#pragma once
#include "entity.hpp"
#include <SFML/Graphics.hpp>

//should be an abstract class, now it's just a normal class
//for testing purposes
class Monster : public Entity
{
    public:

    Monster();

    const std::string GetSpriteName() const;

    void load();

    void update(sf::Time dt);

    private:

    sf::Vector2f velocity_;

    sf::Sprite sprite_;

};