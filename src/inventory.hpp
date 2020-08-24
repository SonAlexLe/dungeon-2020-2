//A class to hold players collected items. A player can hold a single weapon and a single piece of armor.
//Consumable items are easily added. 

#pragma once
#include "item.hpp"
#include "player.hpp"
#include "weapon.hpp"
#include "armor.hpp"
#include "item.hpp"
class Player;
class Inventory{
public:
    Inventory(Player* player) : player_(player)
    {
        weapon_ = nullptr;
        armor_ = nullptr;
    }
    ~Inventory() {}
    void addWeapon(Item* weapon);
    void addArmor(Item* armor);

    float getArmorValue() {
        return armor_->getValue();
    }
    float getDmgValue() {
        return weapon_->getValue();
    }
private:
    Player* player_;
    Item* armor_;
    Item* weapon_;
};