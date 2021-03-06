#include "inventory.hpp"
#include <math.h> 

Inventory::Inventory(Player* player) : player_(player)
{
    armor_ = std::make_unique<Armor>(0.f, 0.f, sf::Vector2f(0.f, 0.f), "Just a regular shirt", player, 0);
    weapon_ = std::make_unique<Weapon>(0.f, 0.f, sf::Vector2f(0.f, 0.f), "Best toy sword", player, 1);
}
std::string Inventory::GetConsumableName() const {
    if (heldConsumable_) {
        return heldConsumable_->getName();
    }
    return "";
}

int Inventory::getArmorValue() {
    if (!armor_) {
        return 0;
    }
    return armor_->getValue();
}

int Inventory::getDmgValue() {
    if (!weapon_) {
        return 0;
    }
    return weapon_->getValue();
}

bool Inventory::hasConsumable() {
    if (!heldConsumable_) {
        return false;
    }
    return true;
}

void Inventory::addItem(std::unique_ptr<Item> newItem)
{
    auto p_room = player_->GetRoom();
    switch (newItem->getType())
    {
    case weapon:
        if (!weapon_)
        {
            weapon_.reset(newItem.release());
        }
        else
        {
            weapon_->setUnequipped();
            weapon_->SetPosition(Drop());
            weapon_->GetSprite().setPosition(Drop());
            p_room->AddItem(std::move(weapon_));
            weapon_.reset(newItem.release());
        }
        p_room = nullptr;
        break;
    case armor:
        if (!armor_) {
            armor_.reset(newItem.release());
        }
        else {
            armor_->setUnequipped();
            armor_->SetPosition(Drop());
            armor_->GetSprite().setPosition(Drop());
            p_room->AddItem(std::move(armor_));
            armor_.reset(newItem.release());
        }
        p_room = nullptr;
        break;
    case consumable:
        if (!heldConsumable_) {
            heldConsumable_.reset(newItem.release());
        }
        else {
            heldConsumable_->setUnequipped();
            heldConsumable_->SetPosition(Drop());
            heldConsumable_->GetSprite().setPosition(Drop());
            p_room->AddItem(std::move(heldConsumable_));
            heldConsumable_.reset(newItem.release());
        }
        p_room = nullptr;
        break;
    }
}

sf::Vector2f Inventory::Drop() { // Function to calculate the spot to drop the held item when a new one is picked up.
    auto p_veloc = player_->GetVelocity();
    auto p_location = player_->GetPosition();
    float unitX = p_veloc.x / (sqrt(pow(p_veloc.x, 2.0f) + pow(p_veloc.y, 2.0f)));
    float unitY = p_veloc.y / (sqrt(pow(p_veloc.x, 2.0f) + pow(p_veloc.y, 2.0f)));
    unitX = unitX * (-1) * 20 + p_location.x;
    unitY = unitY * (-1) * 20 + p_location.y;
    sf::Vector2f v1(unitX, unitY);
    return v1;
}

void Inventory::useConsumable() {
    if (heldConsumable_ != nullptr) {
        heldConsumable_->use();
        heldConsumable_ = nullptr;
    }
    return;
}