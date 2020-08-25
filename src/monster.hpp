#pragma once
#include "entity.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>

class Monster : public Entity
{
    public:

    Monster();

    Monster(float x, float y, sf::Vector2f velocity, int hp, Player* p);

    const std::string GetSpriteName() const;

    sf::Sprite& GetSprite();

    int GetHP();

    void SetHP(int);

    void SetPlayer(Player*);

    Player* GetPlayer();

    protected:

    sf::Texture texture_;

    sf::Sprite sprite_;

    int hp_;

    Player* p_;

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