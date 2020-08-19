#pragma once
#include "config.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include "entity.hpp"
#include <cmath>
#include "inventory.hpp"
#include "room.hpp"
class Inventory;
class Player : public Entity
{
public:

    Player() = delete;

    /** Constructor for Player, initial velocity is 0
     * @param x the x-coord
     * @param y the y-coord
     * @param room the initial room
     */ 
    Player(float x, float y, Room* room);

    void update(sf::Time dt);

    Inventory* GetInventory() { return inventory_; }

    void SetInventory(Inventory* inventory) { inventory_ = inventory; }

    const std::string GetSpriteName() const;

    sf::Sprite& GetSprite();

    float GetReload();

    void Attack();

    void load(){}

    void SetHP(int hp);

    int GetHP();

    //input handling methods, by Leo
    void accUp(bool);
    void accLeft(bool);
    void accDown(bool);
    void accRight(bool);

private:

    sf::Vector2f velocity_;

    sf::Sprite sprite_;

    Inventory* inventory_;

    //for tracking reload rate
    float reload_;

    //input handling, by Leo
    bool accUp_;
    bool accLeft_;
    bool accRight_;
    bool accDown_;
    //hit points
    int hp_;

};