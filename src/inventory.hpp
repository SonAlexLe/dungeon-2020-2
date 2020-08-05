//A class to hold players collected items. A player can hold a single weapon and a single piece of armor.
//Consumable items are easily added. 

#pragma once

#include "player.hpp"
#include "inventoryItem.hpp"
#include "item.hpp"

class Inventory{
public:
    Inventory(Player* player) : player_(player)
    {
        weapon_ = nullptr;
        armor_ = nullptr;
    }
    ~Inventory(){}
    void addWeapon(inventoryItem* weapon);
    void addArmor(inventoryItem* armor);
    
    int getArmorValue(){
        return armor_->getValue();
    }
    int getDmgValue(){
        return weapon_->getValue();
    }
private:
    Player* player_;
    inventoryItem* armor_;
    inventoryItem* weapon_;
};