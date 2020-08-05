//This class provides the items values.

#pragma once
#include "item.hpp"
class inventoryItem{
public:
    inventoryItem(int value, std::string name, int type){
        equipped_ = false;
    }
    inventoryItem(){}

    std::string getName() const;
    int getType() const;
    int getValue() const;
    bool getStatus() const;
    void setUnequipped();
    void setEquipped();

private: 
    int armorDmgValue_;
    bool equipped_; //Value to indicate whether the item is on the ground or inventory. 
    std::string name_;
    int type_; //Value to indicate what the item is.
};