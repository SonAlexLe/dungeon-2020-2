#pragma once
#include "entity.hpp"
#include "player.hpp"
#include "room.hpp"
#include <SFML/Graphics.hpp>

class Monster : public Entity
{
public:

    Monster() = delete;

    /** Constructor for Monster
     * 
     * @param x the x-coord
     * @param y the y-coord
     * @param room the initial room
     * @param velocity the initial velocity
     * @param hp the initial hp
     */
    Monster(float x, float y, Room* room, sf::Vector2f velocity, int hp);

    Monster(float x, float y, sf::Vector2f velocity, int hp, Player* p);

    const std::string GetSpriteName() const;

    sf::Sprite& GetSprite();

    int GetHP();

    void SetHP(int);

    void SetPlayer(Player*);

    Player* GetPlayer();

    protected:

    sf::Texture texture_;

    int hp_;

    sf::Sprite sprite_;

};

class Orc : public Monster
{
    public:
    Orc() = delete;
    Orc(float x, float y, Player* p);
    void update(sf::Time dt);
};

class Orge : public Monster
{
    public:
    Orge() = delete;
    Orge(float x, float y, Player* p);
    void update(sf::Time dt);
};