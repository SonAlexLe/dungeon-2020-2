
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

    Player(Room* room); 

    //Player(float x, float y);

    //void update(std::map<sf::Keyboard::Key, bool>& keys, std::map<sf::Mouse::Button, bool>& mousebutts, sf::Time dt);

    void update(sf::Time dt); // empty function, does not do anything for now

    Inventory* GetInventory() { return inventory_; }

    void SetInventory(Inventory* inventory) { inventory_ = inventory; }

    const std::string GetSpriteName() const;

    Room *GetRoom();

    sf::Sprite& GetSprite();

    float GetReload();

    void Attack();

    void load();

    //input handling methods, by Leo
    void accUp(bool);
    void accLeft(bool);
    void accDown(bool);
    void accRight(bool);

private:

    sf::Sprite sprite_;

    Inventory* inventory_;

    Room* room_;

    //for tracking reload rate
    float reload_;

    //input handling, by Leo
    bool accUp_;
    bool accLeft_;
    bool accRight_;
    bool accDown_;

};