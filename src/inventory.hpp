//A class to hold players collected items. A player can hold a single weapon and a single piece of armor.
#pragma once
#include "inventoryItems.hpp"
#include "item.hpp"
#include <memory>
#include <math.h> 
class player;
class Inventory {
public:
    Inventory(std::shared_ptr<Player> player);
    ~Inventory() {}

    void addItem(std::shared_ptr<Item> newItem);
    int getArmorValue();
    int getDmgValue();
    void useConsumable(); // Uses the held consumable.
    sf::Vector2f Drop();

private: // Player is able to hold one weapon, one armor and one consumable.
    Inventory& operator=(const Inventory&) = delete;

    std::weak_ptr<Player> player_;
    std::shared_ptr<Item> armor_;
    std::shared_ptr<Item> weapon_;
    std::shared_ptr<Item> heldConsumable_;
};