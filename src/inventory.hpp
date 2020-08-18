//A class to hold players collected items. A player can hold a single weapon and a single piece of armor.
//Consumable items are easily added. 

#pragma once
#include "item.hpp"
#include "player.hpp"
#include "weapon.hpp"
#include "armor.hpp"

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

    float getArmorValue() {
        return armor_->getValue();
    }
    float getDmgValue() {
        return weapon_->getValue();
    }
    sf::Vector2f Drop();
private: // Player is able to hold one weapon, one armor and one consumable.
    Inventory& operator=(const Inventory&) = delete;

    Player* player_;
    Item* armor_;
    Item* weapon_;
    Item* heldConsumable_;
};