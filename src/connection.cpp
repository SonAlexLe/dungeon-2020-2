#include "connection.hpp"

Connection::Connection() : Entity() {}

Connection::Connection(float x, float y, std::string f, std::shared_ptr<Player> p) : Entity(x, y, sf::Vector2f()), locked_(true), facing_(f), player_(p) {
    if (!texture_.loadFromFile("src/Sprites/door.png")) std::cout << "sprite error!" << std::endl;
    sprite_.setTexture(texture_);
    sprite_.setOrigin(17.f, 0.f);
    sprite_.setScale(sf::Vector2f(2.4f, 2.4f)); //Change later
    if (facing_ == "south") {
        sprite_.rotate(180.f);
    }
    else if (facing_ == "east") {
        sprite_.rotate(90.f);
    }
    else if (facing_ == "west") {
        sprite_.rotate(270.f);
    }
}

void Connection::unlock() { locked_ = false;}

const std::string Connection::GetSpriteName() const {return "door.png";}

void Connection::update(sf::Time dt) {
    if (this->sprite_.getGlobalBounds().intersects(player_->GetSprite().getGlobalBounds()) ) {
        std::cout << "collision" << std::endl;
        std::cout << "This door is facing: " << facing_ << std::endl;
        traverse();
    }
}

void Connection::load() {}


void Connection::traverse() {
    double size = player_->GetRoom()->GetHeight();
        if (this->facing_ == "north") {

            std::cout << "North door" << std::endl;
            std::shared_ptr<Room> nn = player_->GetRoom()->GetNConn();
            player_->SetRoom(nn);
            std::cout << "Swapped room" << std::endl;
            //player_->SetPosition(sf::Vector2f(150, 150));
            player_->SetPosition(sf::Vector2f(size / 2, size - 30));
        }
        else if (this->facing_ == "south") {

            std::shared_ptr<Room> sn = player_->GetRoom()->GetSConn();
            player_->SetRoom(sn);
            std::cout << "Swapped room" << std::endl;
            //player_->SetPosition(sf::Vector2f(150, 150));
            player_->SetPosition(sf::Vector2f(size / 2, 30.0));
        }
        else if (this->facing_ == "west") {

            std::shared_ptr<Room> wn = player_->GetRoom()->GetWConn();
            player_->SetRoom(wn);
            std::cout << "Swapped room" << std::endl;
            //player_->SetPosition(sf::Vector2f(150, 150));
            player_->SetPosition(sf::Vector2f(size - 30, size / 2));
        }
        else if (this->facing_ == "east") {

            std::shared_ptr<Room> en = player_->GetRoom()->GetEConn();
            player_->SetRoom(en);
            std::cout << "Swapped room" << std::endl;
            //player_->SetPosition(sf::Vector2f(150, 150));
            player_->SetPosition(sf::Vector2f(30.0, size / 2));
        }
}

void Connection::draw(sf::RenderWindow* window) { 
    sprite_.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    window->draw(sprite_);
}
