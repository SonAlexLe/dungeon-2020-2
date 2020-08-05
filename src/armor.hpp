//Very basic class for player armor. Pretty easily modifiable (adding more functions etc.).
#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "item.hpp"
class Armor : public Item
{
public:
    Armor(double x, double y, const std::string name, const int type, Player* player,  int value) :
    Item(x, y, name, type, player, value) {}
    
    void load() //Creates a texture that shows the weapon on the ground. //Loads the picture form a file named "armorOnTheGround.png".
    {
        this->texture_.loadFromFile("armorOnTheGround.png", sf::IntRect(this->currPos_.x, this->currPos_.y, 20, 20)); 
        this->sprite_.setTexture(this->texture_);
    }
};