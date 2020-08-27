#include "inventory.hpp"
#include <math.h> 

Inventory::Inventory(std::shared_ptr<Player> player) : player_(player)
{
    armor_ = std::make_shared<Armor>(0.f, 0.f, sf::Vector2f(0.f, 0.f), "T-shirt", player, 1);
    weapon_ = std::make_shared<Weapon>(0.f, 0.f, sf::Vector2f(0.f, 0.f), "Stick", player, 1);
}


int Inventory::getArmorValue() {
    if (!armor_) {
        return 0;
    }
    return armor_->getValue();
}

int Inventory::getDmgValue() {
    if (!weapon_ ) {
        return 0;
    }
    return weapon_->getValue();
}

void Inventory::addItem(std::shared_ptr<Item> newItem)
{
    switch (newItem->getType())
    {
    case weapon:
        if (!weapon_)
        {
            weapon_ = newItem;
        }
        else
        {
            weapon_->setUnequipped();
            weapon_->SetPosition(Drop());
            weapon_->GetSprite().setPosition(Drop());
            weapon_ = newItem;
        }
        break;
    case armor:
        if (!armor_) {
            this->armor_ = newItem;
        }
        else {
            armor_->setUnequipped();
            armor_->SetPosition(Drop());
            armor_->GetSprite().setPosition(Drop());
            armor_ = newItem;
        }
        break;
    case consumable:
        if (!heldConsumable_) {
            this->heldConsumable_ = newItem;
        }
        else {
            heldConsumable_->setUnequipped();
            heldConsumable_->SetPosition(Drop());
            heldConsumable_->GetSprite().setPosition(Drop());
            heldConsumable_ = newItem;
        }
    }
}

sf::Vector2f Inventory::Drop() { // Function to calculate the spot to drop the held item when a new one is picked up.
    float unitX = player_->GetVelocity().x / (sqrt(pow(player_->GetVelocity().x, 2.0f) + pow(player_->GetVelocity().y, 2.0f)));
    float unitY = player_->GetVelocity().y / (sqrt(pow(player_->GetVelocity().x, 2.0f) + pow(player_->GetVelocity().y, 2.0f)));
    unitX = unitX * (-1) * 115 + player_->GetSprite().getPosition().x;
    unitY = unitY * (-1) * 115 + player_->GetSprite().getPosition().y;
    sf::Vector2f v1(unitX, unitY);
    return v1;
}

void Inventory::useConsumable() {
    if (heldConsumable_) {
        heldConsumable_->use();
        heldConsumable_.reset();
    }
    return;
}