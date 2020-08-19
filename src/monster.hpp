#pragma once
#include "entity.hpp"
#include "room.hpp"
#include <SFML/Graphics.hpp>

//should be an abstract class, now it's just a normal class
//for testing purposes
class Monster : public Entity
{
    public:

    Monster() = delete;
    // constructor for monsters
    Monster(Room* room);

    const std::string GetSpriteName() const;

    void load();

    // void update(sf::Time dt); TODO: AI for subclasses

    private:

    Room* room_;

    sf::Sprite sprite_;

};