//A parent class for the different item (weapons, armor, potions etc.) classes. 
#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "entity.hpp"
#include <memory>

enum ItemTypes { //Types to differentiate the items.
    DEFAULT = 0,
    weapon,
    armor,
    consumable
};
class Player;
class Inventory;
class Item : public Entity { //Inherits from the entity class.
public:
    Item(float x, float y, sf::Vector2f vector, const std::string name, Player* player, int value);
    virtual std::unique_ptr<Item> clone() const = 0;
    std::string getName() const;
    int getType() const;
    int getValue() const;
    bool GetEquipped() const;
    std::string GetName() const;
    sf::Sprite& GetSprite() { return sprite_; }

    void setUnequipped();
    void setEquipped();
    void update(sf::Time dt);
    void draw(sf::RenderWindow* window);
    virtual void load() = 0;
    void use() { return; } // Function for the consumables. Armor and weapon use function does nothing.

protected:
    sf::Texture texture_;
    sf::Sprite sprite_; //Sprite shown when the item is on the ground.
    int armorDmgValue_;
    bool equipped_; //Value to indicate whether the item is on the ground or inventory. 
    std::string name_;
    int type_ = DEFAULT;
    Player* player_;
};





class itemGenerator {
public:
    itemGenerator() { gameLvl_ = 1; };
    ~itemGenerator() {};

    std::unique_ptr<Item> createEquipment(float x, float y, Player* player); // Need to give the position for the created item and the player.
    std::unique_ptr<Item> createConsumable(float x, float y, Player* player); // Creates a random consumable.
private:
    itemGenerator(const itemGenerator&) = delete;
    std::vector<std::string> quality_ = { "Poor", "Good", "Great" }; // Strings to determine the equipment.
    std::vector<std::string> material_ = { "wooden", "bronze", "iron", "platinum" }; // Strings to determine the equipment.
    int gameLvl_;
};