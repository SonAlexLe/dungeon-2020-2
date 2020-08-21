//can also manifest as an entity on the ground, that can be then picked up if it collides with a player.
#include "item.hpp"
#include "player.hpp"
#include "inventory.hpp"
std::string Item::getName() const {
    return name_;
}

int Item::getType() const {
    return type_;
}

float Item::getValue() const {
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