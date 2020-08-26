#include "inventory.hpp"
#include "player.hpp"
#include <math.h> 

int Inventory::getArmorValue() {
    if (armor_ == nullptr) {
        return 0;
    }
    return armor_->getValue();
}

int Inventory::getDmgValue() {
    if (weapon_ == nullptr) {
        return 0;
    }
    return weapon_->getValue();
}

void Inventory::addItem(Item* newItem)
{
    switch (newItem->getType())
    {
    case weapon:
        if (weapon_ == nullptr)
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
        if (this->armor_ == nullptr) {
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
        if (this->heldConsumable_ == nullptr) {
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
    float unitX = player_->GetVelocity().x / (sqrt(pow(player_->GetVelocity().x , 2.0f) + pow(player_->GetVelocity().y, 2.0f)));
    float unitY = player_->GetVelocity().y / (sqrt(pow(player_->GetVelocity().x , 2.0f) + pow(player_->GetVelocity().y, 2.0f)));
    unitX = unitX * (-1) * 115 + player_->GetSprite().getPosition().x;
    unitY = unitY * (-1) * 115 + player_->GetSprite().getPosition().y;
    sf::Vector2f v1(unitX, unitY);
    return v1;
}

void Inventory::useConsumable(){
    if (heldConsumable_ != nullptr) {
        heldConsumable_->use();
        heldConsumable_ = nullptr;
    }
    return;
}