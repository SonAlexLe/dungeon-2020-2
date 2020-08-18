//Very basic class for player armor. Pretty easily modifiable (adding more functions etc.).
#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "item.hpp"
#include "player.hpp"

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