//A parent class for the different item (weapons, armor, potions etc.) classes. 
#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "entity.hpp"

enum ItemTypes { //Types to differentiate the items.
    DEFAULT = 0,
    weapon,
    armor,
    consumable
};
class Player;
class Item : public Entity { //Inherits from the entity class.
public:
    Item(float x, float y, const std::string name, Player* player, float value)
        : Entity(x, y), name_(name), player_(player), armorDmgValue_(value)
    {
        equipped_ = false;
    }

    std::string getName() const;
    int getType() const;
    float getValue() const;
    bool GetEquipped() const;
    sf::Sprite& GetSprite() { return sprite_; }
    void setUnequipped();
    void setEquipped();
    void draw(sf::RenderWindow* window);
    // inherited
    void update(sf::Time dt);
    // load() is also inherited from Entity

protected:
    sf::Texture texture_;
    sf::Sprite sprite_; //Sprite shown when the item is on the ground.
    float armorDmgValue_;
    bool equipped_; //Value to indicate whether the item is on the ground or inventory. 
    std::string name_;
    int type_ = DEFAULT;
    Player* player_;
};