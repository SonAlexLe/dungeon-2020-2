
#include "item.hpp"

void Item::update(sf::Time dt){
    if(item_->getStatus() == false && this->sprite_.getGlobalBounds().intersects(this->player_->sprite_.getGlobalBounds())){ //Checks for collision with the player.
        switch (item_->getType()){
        case 1:
            this->player_->inventory->addWeapon(item_);
            break;
        case 2:
            this->player_->inventory->addArmor(item_);
            break;
        }
    item_->setEquipped();
    }
}

void Item::draw(sf::RenderWindow* window){ //Now only draws the sprite but it also should draw the name of the item under it.
    if(item_->getStatus() == false){ //Draw function should only draw the object if it's not equipped.
        window->draw(this->sprite_);
    }
}

void Item::load() //Loads the picture form the given filename.
{
    this->texture_.loadFromFile(filename_, sf::IntRect(this->currPos_.x, this->currPos_.y, 10, 10));
    this->sprite_.setTexture(this->texture_);
}