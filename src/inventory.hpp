//A class to hold players collected items. A player can hold a single weapon and a single piece of armor.
#pragma once
#include "inventoryItems.hpp"
class player;
class Inventory {
public:
    Inventory(std::shared_ptr<Player> player) : player_(player)
    {
        auto weapon_ = new Weapon(0.f, 0.f,sf::Vector2f(0.f,0.f), "Stick", player, 1); //Starting weapon
        auto armor_ = new Armor(0.f, 0.f,sf::Vector2f(0.f,0.f), "T-shirt", player, 0); //Starting armor
        heldConsumable_ = nullptr;
    }
    ~Inventory() {}

    void addItem(std::shared_ptr<Item> newItem);
    int getArmorValue();
    int getDmgValue();
    void useConsumable(); // Uses the held consumable.
    sf::Vector2f Drop();

private: // Player is able to hold one weapon, one armor and one consumable.
    Inventory& operator=(const Inventory&) = delete;

    std::shared_ptr<Player> player_;
    std::shared_ptr<Item> armor_;
    std::shared_ptr<Item> weapon_;
    std::shared_ptr<Item> heldConsumable_;
};