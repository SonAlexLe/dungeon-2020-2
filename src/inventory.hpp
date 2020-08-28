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

    void addItem(std::unique_ptr<Item> newItem);
    int getArmorValue();
    int getDmgValue();
    bool hasConsumable();
    void useConsumable(); // Uses the held consumable.
    std::string GetConsumableName() const;
    sf::Vector2f Drop();

private: // Player is able to hold one weapon, one armor and one consumable.
    Inventory& operator=(const Inventory&) = delete;

    std::shared_ptr<Player> player_;
    std::unique_ptr<Item> armor_;
    std::unique_ptr<Item> weapon_;
    std::unique_ptr<Item> heldConsumable_;
};