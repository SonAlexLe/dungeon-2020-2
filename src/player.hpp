
#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "entity.hpp"
#include "inventory.hpp"
#include "projectile.hpp"
#include "room.hpp"
class Inventory;
class Player : public Entity
{
public:

    Player();

    Player(Room* room); 

    Player(float x, float y);

    void update(std::map<sf::Keyboard::Key, bool>& keys, std::map<sf::Mouse::Button, bool>& mousebutts, sf::Time dt);

    void update(sf::Time dt) {} // empty function, does not do anything for now

    Inventory* GetInventory() { return inventory_; }

    void SetInventory(Inventory* inventory) { inventory_ = inventory; }

    const std::string GetSpriteName() const;

    sf::Sprite& GetSprite();

    void load();

private:

    sf::Vector2f velocity_;

    sf::Sprite sprite_;

    Inventory* inventory_;

    // for testing purpose
    Projectile projectile_;

    Room* room_;

};