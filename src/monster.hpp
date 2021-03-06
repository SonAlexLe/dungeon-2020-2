#pragma once
#include "entity.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <sstream>

class Monster : public Entity
{
public:

    Monster();
    Monster(float x, float y, sf::Vector2f velocity, int hp, Player* p);

    void Draw(sf::RenderWindow*, sf::Font&, sf::Color c = sf::Color::Transparent);

//Getters and setters
    sf::Sprite& GetSprite();
    int GetHP();
    void SetHP(int);
//if not then it won't be drawn
    bool isActive();
    void setActive(bool);

    void SetPlayer(Player*);
    Player* GetPlayer();

protected:

    //is the monster updated & rendered? 
    bool active_;

    sf::Sprite sprite_;

    int hp_;

    Player* p_;

    void AdjustSpawn();

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
    private:
    float aggro_;
};

class Boss : public Monster
{
    public:
    Boss() = delete;
    Boss(float x, float y, Player* p);
    void update(sf::Time dt);
    private:
    //for circular motion
    sf::Clock clock_;
    //cooldown
    float cooldown_;
    int volley_;
    sf::Vector2f waypoint_;
};