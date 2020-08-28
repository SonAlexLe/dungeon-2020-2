#include "inventory.hpp"
#include <math.h> 

Inventory::Inventory(std::shared_ptr<Player> player) : player_(player)
{
    armor_ = std::make_shared<Armor>(0.f, 0.f, sf::Vector2f(0.f, 0.f), "T-shirt", player, 1);
    weapon_ = std::make_shared<Weapon>(0.f, 0.f, sf::Vector2f(0.f, 0.f), "Stick", player, 1);
}
std::string Inventory::GetConsumableName() const {
    if (heldConsumable_ != nullptr) {
        return heldConsumable_->getName();
    }
    return "";
}

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

bool Inventory::hasConsumable() {
    if (heldConsumable_ == nullptr) {
        return false;
    }
    return true;
}

void Inventory::addItem(const std::shared_ptr<Item>& newItem)
{
    auto p_room = player_.lock()->GetRoom();
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
            p_room->AddItem(weapon_);
            weapon_ = newItem;
        }
        p_room = nullptr;
        break;
    case armor:
        if (this->armor_ == nullptr) {
            this->armor_ = newItem;
        }
        else {
            armor_->setUnequipped();
            armor_->SetPosition(Drop());
            armor_->GetSprite().setPosition(Drop());
            p_room->AddItem(armor_);
            armor_ = newItem;
        }
        p_room = nullptr;
        break;
    case consumable:
        if (this->heldConsumable_ == nullptr) {
            this->heldConsumable_ = newItem;
        }
        else {
            heldConsumable_->setUnequipped();
            heldConsumable_->SetPosition(Drop());
            heldConsumable_->GetSprite().setPosition(Drop());
            p_room->AddItem(heldConsumable_);
            heldConsumable_ = newItem;
        }
        p_room = nullptr;
        break;
    }
}

sf::Vector2f Inventory::Drop() { // Function to calculate the spot to drop the held item when a new one is picked up.
    if (player_.expired()) return sf::Vector2f(0, 0); // is player object destroyed?
    auto p_veloc = player_.lock()->GetVelocity();
    auto p_location = player_.lock()->GetPosition();
    float unitX = p_veloc.x / (sqrt(pow(p_veloc.x, 2.0f) + pow(p_veloc.y, 2.0f)));
    float unitY = p_veloc.y / (sqrt(pow(p_veloc.x, 2.0f) + pow(p_veloc.y, 2.0f)));
    unitX = unitX * (-1) * 40 + p_location.x;
    unitY = unitY * (-1) * 40 + p_location.y;
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