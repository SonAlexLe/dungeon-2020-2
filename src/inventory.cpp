#include "inventory.hpp"

void Inventory::addWeapon(Item* newWeapon) {
    if (this->weapon_ == nullptr) {
        this->weapon_ = newWeapon;
    }
    else {
        weapon_->setUnequipped();
        sf::Vector2f v1(player_->GetPosition().x + 10, player_->GetPosition().x); //I havent figured out yet a proper way to place items back on the ground. This is a temporary solution.
        weapon_->SetPosition(v1);
        weapon_ = newWeapon;
    }
}

void Inventory::addArmor(Item* newArmor) {
    if (this->armor_ == nullptr) {
        this->armor_ = newArmor;
    }
    else {
        armor_->setUnequipped();
        sf::Vector2f v1(player_->GetPosition().x + 10, player_->GetPosition().x);
        armor_->SetPosition(v1);
        armor_ = newArmor;
    }
}