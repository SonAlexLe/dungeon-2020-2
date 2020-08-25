#include "inventoryItems.hpp"
#include "player.hpp"
#include <string>

void Armor::load() {
    this->texture_.loadFromFile("armorOnTheGround.png");
    this->sprite_.setTexture(this->texture_);
}

void Weapon::load() {
    this->texture_.loadFromFile("weaponOnTheGround.png");
    this->sprite_.setTexture(this->texture_);
}


void HealingPotion::load() {
    this->texture_.loadFromFile("consumableOnTheGround.png");
    this->sprite_.setTexture(this->texture_);
}

void HealingPotion::use() {
    // player_->SetHPtoMax();
    delete this;
}