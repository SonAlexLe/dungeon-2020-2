//Very basic class for player weapon. Pretty easily modifiable (adding more functions etc.).

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <Time.hpp>
#include "item.hpp"

class Weapon : public Item
{
private:
    sf::Time attackInterval; //attackInterval value tells how often the player can attack with the weapon.
                            //The greater the attacking value of the weapon is the less often the player can attack.
public:
    Weapon(double x, double y, const std::string name, const int type, Player* player,  int value) :
    Item(x, y, name, type, player, value)
    {
        attackInterval = sf::seconds(0.1 * value);
    }
    
    void load() //Loads the picture form a file named "weaponOnTheGround.png".
    {
        this->texture_.loadFromFile(weaponOnTheGround.png, sf::IntRect(this->currPos_.x, this->currPos_.y, 10, 10));
        this->sprite_.setTexture(this->texture_);
    }
};

