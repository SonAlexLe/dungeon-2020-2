//Very basic class for player armor. Pretty easily modifiable (adding more functions etc.).
#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "item.hpp"
#include "player.hpp"

class Armor : public Item
{
public:
    Armor(float x, float y, const std::string name, const int type, Player* player, float value) :
        Item(x, y, name, type, player, value) {}

    void load() //Creates a texture that shows the armor on the ground. //Loads the picture form a file named "armorOnTheGround.png".
    {
        this->texture_.loadFromFile("pshychobot.png");
        this->sprite_.setTexture(this->texture_);
    }
};