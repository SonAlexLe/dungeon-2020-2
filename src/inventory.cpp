#include "inventory.hpp"

void Inventory::addWeapon(inventoryItem* newWeapon){ //This function is not finished.
    if(this->weapon_ == nullptr){
        this->weapon_ = newWeapon;
    }
    else{
        weapon_->setUnequipped(); 
        weapon_ = newWeapon;
    }
}

void Inventory::addArmor(inventoryItem* newArmor){ //This function is not finished.
    if(this->armor_ == nullptr){
        this->armor_ = newArmor;
    }
    else{
        armor_->setUnequipped();
        armor_ = newArmor;
    }
}