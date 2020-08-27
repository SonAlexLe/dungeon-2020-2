#include "connection.hpp"

Connection::Connection() : Entity() {}

Connection::Connection(float x, float y, std::string f, std::shared_ptr<Player> p) : Entity(x, y, sf::Vector2f()), locked_(true), facing_(f), player_(p) {
    if (!texture_.loadFromFile("src/Sprites/door.png")) std::cout << "sprite error!" << std::endl;
    sprite_.setTexture(texture_);
    sprite_.setScale(sf::Vector2f(2.4f, 2.4f)); //Change later
    //code below copied from monster::adjustspawn()
    auto bounds = sprite_.getGlobalBounds();
    if (currPos_.x+bounds.width/3 > p->GetRoom()->GetWidth()-1)
        currPos_ = sf::Vector2f(p->GetRoom()->GetWidth()-bounds.width/3, currPos_.y);
    if (currPos_.y+bounds.height/3 > p->GetRoom()->GetHeight()-1)
        currPos_ = sf::Vector2f(currPos_.x, p->GetRoom()->GetHeight()-bounds.height/3);
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
            player_->SetPosition(sf::Vector2f(150, 150));
            //player_->SetPosition(sf::Vector2f(size / 2, size));
        }
        else if (this->facing_ == "south") {

            std::shared_ptr<Room> sn = player_->GetRoom()->GetSConn();
            player_->SetRoom(sn);
            std::cout << "Swapped room" << std::endl;
            player_->SetPosition(sf::Vector2f(150, 150));
            //player_->SetPosition(sf::Vector2f(size / 2, 0.0));
        }
        else if (this->facing_ == "west") {

            std::shared_ptr<Room> wn = player_->GetRoom()->GetWConn();
            player_->SetRoom(wn);
            std::cout << "Swapped room" << std::endl;
            player_->SetPosition(sf::Vector2f(150, 150));
            //player_->SetPosition(sf::Vector2f(size, size / 2));
        }
        else if (this->facing_ == "east") {

            std::shared_ptr<Room> en = player_->GetRoom()->GetEConn();
            player_->SetRoom(en);
            std::cout << "Swapped room" << std::endl;
            player_->SetPosition(sf::Vector2f(150, 150));
            //player_->SetPosition(sf::Vector2f(0.0, size / 2));
        }
}

void Connection::draw(sf::RenderWindow* window) { 
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
