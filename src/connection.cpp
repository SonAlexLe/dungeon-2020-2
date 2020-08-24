#include "connection.hpp"

Connection::Connection() : Entity() {}

Connection::Connection(float x, float y) : Entity(x, y), locked_(true) {}

void Connection::unlock() { locked_ = false;}

//Needs to be updated once sprites are figured out
const std::string Connection::GetSpriteName() const {return "door.png";}

void Connection::update(sf::Time dt) {}

void Connection::load() {}

//Should probably be on update
void Connection::traverse(Player* p) {
    if(locked_ == false && this->sprite_.getGlobalBounds().intersects(p->GetSprite().getGlobalBounds())){ //Checks collision 
        if (currPos_.x == 50.0 && currPos_.y == 0.0) { //Connection is north
            /*
            p->room_ = connected_to_;
            p->currPos_ = 100.0 50.0 */
        if (currPos_.x == 100.0 && currPos_.y == 50.0) {
            /*
            p->room_ = connected_to_;
            p->currPos_ = 0.0 50.0 */
        }
        if (currPos_.x == 50.0 && currPos_.y == 100.0) {
            /*
            p->room_ = connected_to_;
            p->currPos_ = 50.0 0.0 */
        }
        if (currPos_.x == 50.0 && currPos_.y == 100.0) {
            /*
            p->room_ = connected_to_;
            p->currPos_ = 50.0 0.0 */
        }
    }
    }  
}

void Connection::draw(sf::RenderWindow* window) { //Now only draws the sprite but it also should draw the name of the item under it.
    if(this->locked_ == false){ //Draw function should only draw the object if it's not equipped.
        window->draw(this->sprite_);
    }
