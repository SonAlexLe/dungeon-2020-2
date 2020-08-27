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
    Player(std::shared_ptr<Room> room); 
    ~Player() {}

    //inventory management methods
    std::shared_ptr<Inventory> GetInventory() { return inventory_; }
    void SetInventory(std::shared_ptr<Inventory> inventory) { inventory_ = inventory; }

    //Getters for interfacing
    std::shared_ptr<Room> GetRoom();

    void SetRoom(std::shared_ptr<Room> r);

    sf::Sprite& GetSprite();
    float GetReload();

    bool CanDie() {if(immortal_ == 0) {return true;} else {return false;}}
    void Immortal() { immortal_ = 1;}

    //sets reload time based on the current weapon
    void Attack();

    //input handling methods, determine behavior on player update
    void accUp(bool);
    void accLeft(bool);
    void accDown(bool);
    void accRight(bool);

    //hp & score access and management
    void SetHP(int hp) { hp_ = hp; }
    int GetHP() { return hp_; }
    int GetScore() { return score_; }
    void AddScore(int b) { score_ += b; }

    //Update methods
    void update(sf::Time dt);
    void Draw(sf::RenderWindow*);

private:

    sf::Texture texture_;
    sf::Sprite sprite_;

    std::shared_ptr<Inventory> inventory_;
    std::shared_ptr<Room> room_;

    //input handling
    bool accUp_;
    bool accLeft_;
    bool accRight_;
    bool accDown_;

    //for tracking reload rate
    float reload_;

    int score_;
    int hp_;
    //for invincibility frames
    float immortal_;


};