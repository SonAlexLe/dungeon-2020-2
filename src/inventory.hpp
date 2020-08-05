//A class to hold players collected items. A player can hold a single weapon and a single piece of armor.
//Consumable items are easily added. 

#pragma once

#include "player.hpp"
#include "weapon.hpp"
#include "armor.hpp"
#include "item.hpp"
class Player;
class Inventory{
public:
    Inventory(Player* player) : player_(player)
    {
        weapon_ = new Weapon(0, 0, "Stick", 1, player, 1); //Creates a basic weapon for the player.
        weapon_->setEquipped();
        armor_ = nullptr;
    }
    ~Inventory(){}
    void addWeapon(Weapon* weapon);
    void addArmor(Armor* armor);
    
    int getArmorValue(){
        return armor_->getValue();
    }
    int getDmgValue(){
        return weapon_->getValue();
    }
private:
    Player* player_;
    Armor* armor_;
    Weapon* weapon_;
};