#pragma once
#include "entity.hpp"
#include "room.hpp"
#include <SFML/Graphics.hpp>

class Monster : public Entity
{
    public:

    Monster() = delete;
    // constructor for monsters
    Monster(Room* room, int hp);

    const std::string GetSpriteName() const;

    int GetHP();

    void SetHP(int hp);

    void load();

    protected:

    int hp_;

    Room* room_;

    sf::Sprite sprite_;

};

class Orc : public Monster
{
    public:
    Orc() = delete;
    Orc(Room* room);
    void update(sf::Time dt);
};