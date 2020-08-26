#include "connection.hpp"

Connection::Connection() : Entity() {}

Connection::Connection(float x, float y, std::string f, Player* p) : Entity(x, y, sf::Vector2f()), locked_(true), facing_(f), player_(p) {
    if (!texture_.loadFromFile("src/Sprites/door.png")) std::cout << "sprite error!" << std::endl;
    sprite_.setTexture(texture_);
    sprite_.setScale(sf::Vector2f(3.4f, 3.4f)); //Change later
}

void Connection::unlock() { locked_ = false;}

const std::string Connection::GetSpriteName() const {return "door.png";}

void Connection::update(sf::Time dt) {
    if (sprite_.getGlobalBounds().intersects(player_->GetSprite().getGlobalBounds())) {
        traverse();
    }
}

void Connection::load() {}

void Connection::traverse() {
    /* double size = player_->GetRoom()->GetHeight();
        if (currPos_.x == size / 2 && currPos_.y == 0.0) { //Connection is north
            std::cout << "North door" << std::endl;

            Room* nn = player_->GetRoom()->GetNConn();
            player_->SetRoom(nn);
            std::cout << "Swapped room" << std::endl;
            player_->SetPosition(sf::Vector2f(size / 2, size));
            
        if (currPos_.x == size && currPos_.y == size / 2) { // South
            std::cout << "South door" << std::endl;

            Room* sn = player_->GetRoom()->GetSConn();
            player_->SetRoom(sn);
            std::cout << "Swapped room" << std::endl;
            player_->SetPosition(sf::Vector2f(size / 2, 0.0));
        }
        if (currPos_.x == 0 && currPos_.y == size / 2) { // West
            std::cout << "West door" << std::endl;

            Room* wn = player_->GetRoom()->GetWConn();
            player_->SetRoom(wn);
            std::cout << "Swapped room" << std::endl;
            player_->SetPosition(sf::Vector2f(size, size / 2));
        }
        if (currPos_.x == size && currPos_.y == size / 2) { // East
            std::cout << "East door" << std::endl;

            Room* en = player_->GetRoom()->GetEConn();
            player_->SetRoom(en);
            std::cout << "Swapped room" << std::endl;
            player_->SetPosition(sf::Vector2f(0.0, size / 2));
        }
    }
    */
   std::cout << "This room is facing: " << facing_ << std::endl;
    player_->SetPosition(sf::Vector2f(200, 200));
    std::cout << "Collision!" << std::endl;
}

void Connection::draw(sf::RenderWindow* window) { 
    // if(this->locked_ == false){}

    sf::FloatRect m_rec = sprite_.getGlobalBounds();
    sf::RectangleShape m_box(sf::Vector2f(m_rec.width, m_rec.height));
    m_box.setOutlineThickness(2);
    m_box.setOutlineColor(sf::Color::Blue);
    m_box.setFillColor(sf::Color::Transparent);
    m_box.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    window->draw(m_box);
    sprite_.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    window->draw(sprite_);
    
}