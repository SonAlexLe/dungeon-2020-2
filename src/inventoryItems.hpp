//All of the different item classes are declared here.
#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <ctime>
#include <string>
#include "item.hpp"
#include "player.hpp"
#include <memory>
class Armor : public Item
{
public:
    Armor(float x, float y, sf::Vector2f vector, const std::string name, std::shared_ptr<Player> player, int value);

    Armor() = delete;

    const std::string GetSpriteName() const { return "armorOnTheGround.png"; }

    void load(); //Creates a texture that shows the armor on the ground. Loads the picture form a file named "armorOnTheGround.png".
};


class Weapon : public Item
{
public:
    Weapon(float x, float y, sf::Vector2f vector, const std::string name, std::shared_ptr<Player> player, int value);

    Weapon() = delete;

    const std::string GetSpriteName() const { return "weaponOnTheGround.png"; }

    void load(); //Loads the picture form a file named "weaponOnTheGround.png".

private:
    sf::Time attackInterval; //attackInterval value tells how often the player can attack with the weapon.

};

class HealingPotion : public Item // Single use item that heals the player to full hp.
{
public:
    HealingPotion(float x, float y, sf::Vector2f vector, const std::string name, std::shared_ptr<Player> player, int value);

    HealingPotion() = delete;

    const std::string GetSpriteName() const { return "consumableOnTheGround.png"; }

    void use();

    void load(); //Creates a texture that shows the armor on the ground. Loads the picture form a file named "armorOnTheGround.png".
};


