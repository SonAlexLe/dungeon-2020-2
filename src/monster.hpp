#pragma once
#include "entity.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>

class Monster : public Entity
{
public:

    Monster();
    Monster(float x, float y, sf::Vector2f velocity, int hp, std::shared_ptr<Player> p);

    void Draw(sf::RenderWindow*);

//Getters and setters
    sf::Sprite& GetSprite();
    int GetHP();
    void SetHP(int);

    bool isActive();

    void SetPlayer(std::shared_ptr<Player>);
    std::shared_ptr<Player> GetPlayer();

protected:

    //is the monster updated & rendered? 
    bool active_;

    sf::Texture texture_;
    sf::Sprite sprite_;

    int hp_;

    std::shared_ptr<Player> p_;

};

class Orc : public Monster
{
    public:
    Orc() = delete;
    Orc(float x, float y, std::shared_ptr<Player> p);
    void update(sf::Time dt);
};

class Orge : public Monster
{
    public:
    Orge() = delete;
    Orge(float x, float y, std::shared_ptr<Player> p);
    void update(sf::Time dt);
    float aggro_;
};