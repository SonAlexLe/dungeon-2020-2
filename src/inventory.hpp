//A class to hold players collected items. A player can hold a single weapon and a single piece of armor.
#pragma once
#include "inventoryItems.hpp"
class player;
class Inventory {
public:
    Inventory(Player* player) : player_(player)
    {
        weapon_ = nullptr;
        armor_ = nullptr;
        heldConsumable_ = nullptr;
    }
    ~Inventory() {}

    void addItem(Item* newItem);
    int getArmorValue();
    int getDmgValue();
    void useConsumable(); // Uses the held consumable.
    sf::Vector2f Drop();

private: // Player is able to hold one weapon, one armor and one consumable.
    Inventory& operator=(const Inventory&) = delete;

    Player* player_;
    Item* armor_;
    Item* weapon_;
    Item* heldConsumable_;
};