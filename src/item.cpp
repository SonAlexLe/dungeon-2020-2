//can also manifest as an entity on the ground, that can be then picked up if it collides with a player.
#include "item.hpp"
#include "player.hpp"
#include "inventory.hpp"
#include <stdlib.h>     
#include <time.h>       

// Item class functions below.
std::string Item::getName() const {
    return name_;
}

int Item::getType() const {
    return type_;
}

int Item::getValue() const {
    return armorDmgValue_;
}
bool Item::GetEquipped() const {
    return equipped_;
}

void Item::setUnequipped() {
    equipped_ = false;
}
void Item::setEquipped() {
    equipped_ = true;
}
void Item::update(sf::Time dt) {
    if (equipped_ == false && this->sprite_.getGlobalBounds().intersects(this->player_->GetSprite().getGlobalBounds())) { //Checks for collision with the player.
        this->player_->GetInventory()->addItem(this);
        this->equipped_ = true;
    }
}

void Item::draw(sf::RenderWindow* window) { //Now only draws the sprite but it also should draw the name of the item under it.
    if (this->equipped_ == false) { //Draw function should only draw the object if it's not equipped.
        sprite_.setPosition(this->currPos_);
        window->draw(this->sprite_);
    }
}



// ------------------------------
// itemGenerator functions below.

Item* itemGenerator::createEquipment(float x, float y, Player* player) { // Creates randomly an armor or a weapon for the item room.
    srand((unsigned int)time(NULL));
    int armorWeapon = rand() % 1 + 0;
    int quality = rand() % 2 + 0;
    int material = gameLvl_;
    int material_koht = gameLvl_ - 1;
    std::string name = quality_[quality] + material_[material_koht];
    int equipmentValue = quality + material;
    sf::Vector2f v1(0.f, 0.f);
    if (armorWeapon == 0) {
        name += "weapon";
        Weapon* new_item = new Weapon(x, y, v1, name, player, equipmentValue);
        return new_item;
    }
    else {
        name += "armor";
        Armor* new_item = new Armor(x, y, v1, name, player, equipmentValue);
        return new_item;
    }
}

Item* itemGenerator::createConsumable(float x, float y, Player* player) { //At the moment this function can only create healing potions so the two lines are commented.
    //srand((unsigned int)time(NULL)); 
    //int random_cons = rand() % 1 + 0;
    sf::Vector2f v1(0.f, 0.f);
    HealingPotion* new_cons = new HealingPotion(x, y, v1, "HealingPotion", player, 0);
    return new_cons;
}