#include "inventoryItems.hpp"
#include "player.hpp"
#include <string>
Armor::Armor(float x, float y, sf::Vector2f vector, const std::string name, Player* player, int value)
    : Item(x, y, vector, name, player, value)
{
    type_ = armor;
    this->load();
}
void Armor::load() {
    sprite_ = sf::Sprite(player_->GetTexture(), sf::IntRect(80, 145, 16, 16));
    sprite_.setScale(sf::Vector2f(2, 2));
}
std::unique_ptr<Item> Armor::clone() const {
    return std::make_unique<Armor>(*this);
}

std::unique_ptr<Item> Weapon::clone() const {
    return std::make_unique<Weapon>(*this);
}

std::unique_ptr<Item> HealingPotion::clone() const {
    return std::make_unique<HealingPotion>(*this);
}

Weapon::Weapon(float x, float y, sf::Vector2f vector, const std::string name, Player* player, int value)
    : Item(x, y, vector, name, player, value)
{
    type_ = weapon;
    attackInterval = sf::seconds(0.1f * value);
    this->load();
}
void Weapon::load() {
    sprite_ = sf::Sprite(player_->GetTexture(), sf::IntRect(190, 10, 16, 25));
    sprite_.setScale(sf::Vector2f(2, 2));
}



HealingPotion::HealingPotion(float x, float y, sf::Vector2f vector, const std::string name, Player* player, int value) :
    Item(x, y, vector, name, player, value)
{
    type_ = consumable;
    this->load();
}
void HealingPotion::load() {
    sprite_ = sf::Sprite(player_->GetTexture(), sf::IntRect(32, 160, 16, 16));
    sprite_.setScale(sf::Vector2f(2, 2));
}
void HealingPotion::use() {
    player_->SetHP(player_->GetHP() + 10);
    delete this;
}