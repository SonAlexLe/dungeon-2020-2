 
//can also manifest as an entity on the ground, that can be then picked up if it collides with a player.
#include "item.hpp"

std::string Item::getName() const{
    return name_;
}

int Item::getType() const{
    return type_;
}

int Item::getValue() const{
    return armorDmgValue_;
}
void Item::setUnequipped(){
    equipped_ = false;
}
void Item::setEquipped(){
    equipped_ = true;
}
void Item::update(sf::Time dt){
    if(equipped_ == false && this->sprite_.getGlobalBounds().intersects(this->player_->GetSprite().getGlobalBounds())){ //Checks for collision with the player.
        switch (type_){
        case 1:
            this->player_->GetInventory()->addWeapon(this);
            break;
        case 2:
            this->player_->GetInventory()->addArmor(this);
            break;
        }
    equipped_ = true;
    }
}

void Item::draw(sf::RenderWindow* window){ //Now only draws the sprite but it also should draw the name of the item under it.
    if(this->equipped_ == false){ //Draw function should only draw the object if it's not equipped.
        window->draw(this->sprite_);
    }
}