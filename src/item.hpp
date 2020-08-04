//A parent class for the different item (weapons, armor, potions etc.) classes. 
#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "entity.hpp"
#include "player.hpp"

enum ItemTypes { //Types to differentiate the items.
    DEFAULT = 0,
    weapon,
    armor
};

class Item : public Entity{ //Inherits from the entity class.
public:
    Item(double x, double y, const std::string name, const int type, Player* player, int value)
     : Entity(x, y), name_(name), type_(type), player_(player), armorDmgValue_(value)
    {
        equipped_ = false;
    }

    std::string getName() const;
    int getType() const;
    int getValue() const;
    void setUnequipped();
    void setEquipped();
    void draw(sf::RenderWindow* window);
    // inherited
    void update(sf::Time dt);
    // load() is also inherited from Entity

protected:
    sf::Texture texture_; 
    sf::Sprite sprite_; //Sprite shown when the item is on the ground.
    int armorDmgValue_;
    bool equipped_; //Value to indicate whether the item is on the ground or inventory. 
    std::string name_;
    int type_;
    Player* player_;
};