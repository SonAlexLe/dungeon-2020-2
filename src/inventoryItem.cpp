#include "inventoryItem.hpp"

std::string inventoryItem::getName() const{
    return name_;
}

int inventoryItem::getType() const{
    return type_;
}

int inventoryItem::getValue() const{
    return armorDmgValue_;
}

bool inventoryItem::getStatus() const{
    return equipped_;
}

void inventoryItem::setUnequipped(){
    equipped_ = false;
}

void inventoryItem::setEquipped(){
    equipped_ = true;
}