//All of the different item classes are declared here.
#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "item.hpp"
#include "player.hpp"
#include <ctime>

class Armor : public Item
{
public:
    Armor(float x, float y, const std::string name, Player* player, float value) :
        Item(x, y, name, player, value) 
    {
        type_ = armor;
    }
    const std::string GetSpriteName() const { return "armorOnTheGround.png"; }
    void load() //Creates a texture that shows the armor on the ground. //Loads the picture form a file named "armorOnTheGround.png".
    {
        this->texture_.loadFromFile("armorOnTheGround.png");
        this->sprite_.setTexture(this->texture_);
    }
};


class Weapon : public Item {
public:
    Weapon(float x, float y, const std::string& name, Player* player, float value) :
        Item(x, y, name, player, value)
    {
        type_ = weapon;
        attackInterval = sf::seconds(0.1f * value);
    }

    const std::string GetSpriteName() const { return "weaponOnTheGround.png"; }

    void load() //Loads the picture form a file named "weaponOnTheGround.png".
    {
        this->texture_.loadFromFile("weaponOnTheGround.png");
        this->sprite_.setTexture(this->texture_);
    }
private:
    sf::Time attackInterval; //attackInterval value tells how often the player can attack with the weapon.

};

class HealingPotion : public Item { // Single use item that heals the player to full hp.
public:
    HealingPotion(float x, float y, const std::string& name, Player* player, float value) :
        Item(x, y, name, player, value)
    {
        type_ = consumable;
    }
    const std::string GetSpriteName() const { return "consumableOnTheGround.png"; }

    void use()
    {
        //player_->SetHPtoMax();
        delete this;
    }
    
    void load() {
        this->texture_.loadFromFile("consumableOnTheGround.png");
        this->sprite_.setTexture(this->texture_);
    }
};