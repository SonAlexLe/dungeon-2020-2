//Very basic class for player weapon. Pretty easily modifiable (adding more functions etc.).

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <ctime>
#include "item.hpp"

class Weapon : public Item
{
protected:
    float attackInterval_; //attackInterval value tells how often the player can attack with the weapon.
                            //The greater the attacking value of the weapon is the less often the player can attack.
public:
    Weapon(float x, float y, const std::string& name, const int type, Player* player,  int value) :
    Item(x, y, name, type, player, value)
    {
        attackInterval_ = value;
    }

    const std::string GetSpriteName() const { return "weaponOnTheGround.png"; }
    
    void load() //Loads the picture form a file named "weaponOnTheGround.png".
    {
        this->texture_.loadFromFile("weaponOnTheGround.png", sf::IntRect(this->currPos_.x, this->currPos_.y, 10, 10));
        this->sprite_.setTexture(this->texture_);
    }
};

