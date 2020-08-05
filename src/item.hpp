//Class for showing the item visually on the ground.
#pragma once

#include <string>
#include "entity.hpp"
#include "player.hpp"
#include "inventoryItem.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

enum ItemTypes { //Types to differentiate the items.
    DEFAULT = 0,
    weapon,
    armor
};

class Item : public Entity{ //Inherits from the entity class.
public:
    Item(double x, double y, const std::string name, const int type, Player* player, int value, const std::string filename)
     : Entity(x, y), filename_(filename)
    {
        item_ = new inventoryItem(value, name, type);
    }

    void load();
    void draw(sf::RenderWindow* window);
    void update(sf::Time dt);
private:
    std::string filename_;
    sf::Texture texture_; 
    sf::Sprite sprite_; //Sprite shown when the item is on the ground.

    inventoryItem* item_;
    Player* player_;
};