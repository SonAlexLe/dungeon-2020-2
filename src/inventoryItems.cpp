#include "inventoryItems.hpp"
#include "player.hpp"
#include <string>

Armor::Armor(float x, float y, const std::string name, Player* player, int value) :
    Item(x, y, name, player, value) {type_ = armor;}

void Armor::load() {
    this->texture_.loadFromFile("armorOnTheGround.png");
    this->sprite_.setTexture(this->texture_);
}

Weapon::Weapon(float x, float y, const std::string& name, Player* player, int value) : Item(x, y, name, player, value)
{
    type_ = weapon;
    attackInterval = sf::seconds(0.1f * value);
}

void Weapon::load() {
    this->texture_.loadFromFile("weaponOnTheGround.png");
    this->sprite_.setTexture(this->texture_);
}

HealingPotion::HealingPotion(float x, float y, const std::string& name, Player* player, int value) : 
    Item(x, y, name, player, value) {type_ = consumable;}

void HealingPotion::load() {
    this->texture_.loadFromFile("consumableOnTheGround.png");
    this->sprite_.setTexture(this->texture_);
}

void HealingPotion::use() {
    // player_->SetHPtoMax();
    delete this;
}