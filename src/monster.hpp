#pragma once
#include "entity.hpp"
#include "room.hpp"
#include <SFML/Graphics.hpp>

class Monster : public Entity
{
public:

    Monster() = delete;

<<<<<<< HEAD
=======
    Monster() = delete;

>>>>>>> mapgen
    /** Constructor for Monster
     * 
     * @param x the x-coord
     * @param y the y-coord
     * @param room the initial room
     * @param velocity the initial velocity
     * @param hp the initial hp
     */
    Monster(float x, float y, Room* room, sf::Vector2f velocity, int hp);

    const std::string GetSpriteName() const;

    int GetHP();

    void SetHP(int hp);
<<<<<<< HEAD

    void load();

protected:
=======

    void load();

    protected:
>>>>>>> mapgen

    sf::Vector2f velocity_;

    int hp_;

<<<<<<< HEAD
=======
    Room* room_;

>>>>>>> mapgen
    sf::Sprite sprite_;

};

class Orc : public Monster
{
    public:
    Orc() = delete;
    Orc(float x, float y, Room* room);
    void update(sf::Time dt);
};