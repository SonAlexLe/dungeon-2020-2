#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "config.hpp"
#include "entity.hpp"
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

    void update(sf::Time);

    Inventory* GetInventory() { return inventory_; }

    void SetInventory(Inventory* inventory) { inventory_ = inventory; }

    const std::string GetSpriteName() const;

    Room *GetRoom();

    sf::Sprite& GetSprite();

    float GetReload();

    void Attack();

    //input handling methods, by Leo
    void accUp(bool);
    void accLeft(bool);
    void accDown(bool);
    void accRight(bool);

private:

    sf::Texture texture_;

    sf::Sprite sprite_;

    Inventory* inventory_;

    sf::Vector2f velocity_;

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