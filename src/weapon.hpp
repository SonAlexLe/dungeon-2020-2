//Very basic class for player weapon. Pretty easily modifiable (adding more functions etc.).
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <ctime>


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