#include "connection.hpp"

Connection::Connection() : Entity() {}

Connection::Connection(float x, float y, std::string f, std::shared_ptr<Player> p) : Entity(x, y, sf::Vector2f()), facing_(f), player_(p) {
    if (!texture_.loadFromFile("src/Sprites/door.png")) std::cout << "sprite error!" << std::endl;
    sprite_.setTexture(texture_);
    //Rotate the door based on its facing
    sprite_.setOrigin(17.f, 0.f);
    sprite_.setScale(sf::Vector2f(2.4f, 2.4f));

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

void Connection::update(sf::Time dt) {
    //Check whether the door and player collided, if so move the player
    if (this->sprite_.getGlobalBounds().intersects(player_->GetSprite().getGlobalBounds()) ) {
        traverse();
    }
}

void Connection::traverse() {
    double size = player_->GetRoom()->GetHeight();

        /*Check the facing of the door updated and transport the player to the corresponding neighbor
        Also change the players position so it appears that they've gone through door on the other side
        */
        if (this->facing_ == "north") {

            Room* nn = player_->GetRoom()->GetNConn();
            player_->SetRoom(nn);
            player_->SetPosition(sf::Vector2f(size / 2, size - 30));
        }
        else if (this->facing_ == "south") {

            Room* sn = player_->GetRoom()->GetSConn();
            player_->SetRoom(sn);
            player_->SetPosition(sf::Vector2f(size / 2, 30.0));
        }
        else if (this->facing_ == "west") {

            Room* wn = player_->GetRoom()->GetWConn();
            player_->SetRoom(wn);
            player_->SetPosition(sf::Vector2f(size - 30, size / 2));
        }
        else if (this->facing_ == "east") {

            Room* en = player_->GetRoom()->GetEConn();
            player_->SetRoom(en);
            player_->SetPosition(sf::Vector2f(30.0, size / 2));
        }
}

void Connection::draw(sf::RenderWindow* window) { 
    sprite_.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    window->draw(sprite_);
}


