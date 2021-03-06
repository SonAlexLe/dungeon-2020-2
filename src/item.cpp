//can also manifest as an entity on the ground, that can be then picked up if it collides with a player.
#include "item.hpp"
#include "player.hpp"
#include "inventory.hpp"
#include <stdlib.h>     
#include <time.h>       
#include <random>

// Item class functions below.
Item::Item(float x, float y, sf::Vector2f vector, const std::string name, Player* player, int value) :
    Entity(x, y, vector), name_(name), player_(player), armorDmgValue_(value)
{
    equipped_ = false;
}


std::string Item::getName() const {
    return name_;
}

int Item::getType() const {
    return type_;
}
std::string Item::GetName() const {
    return this->name_;
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
    if (equipped_ == false && this->sprite_.getGlobalBounds().intersects(this->player_->GetSprite().getGlobalBounds())) {
        //Checks for collision with the player.
        this->equipped_ = true;
        this->player_->GetInventory()->addItem(std::move(clone()));
    }
}

void Item::draw(sf::RenderWindow* window, sf::Font& f) { //Now only draws the sprite but it also should draw the name of the item under it.
    if (this->equipped_ == false) { //Draw function should only draw the object if it's not equipped.
        sf::FloatRect m_rec = sprite_.getGlobalBounds();
        sf::RectangleShape m_box(sf::Vector2f(m_rec.width, m_rec.height));
        m_box.setOutlineThickness(2);
        m_box.setOutlineColor(sf::Color::Transparent);
        m_box.setFillColor(sf::Color::Transparent);
        m_box.setPosition(sf::Vector2f(currPos_.x * 3, currPos_.y * 3));
        window->draw(m_box);
        sprite_.setPosition(sf::Vector2f(currPos_.x * 3, currPos_.y * 3));
        window->draw(sprite_);
        std::stringstream ss;
        ss << name_;
        sf::Text name;
        name.setFont(f);
        name.setString(ss.str());
        name.setCharacterSize(12);
        auto bounds = name.getGlobalBounds();
        if (type_ == armor || type_ == weapon) {
            name.setPosition(currPos_.x * 3 - 25, currPos_.y * 3 - 15);
        }
        else {
            name.setPosition(currPos_.x * 3, currPos_.y * 3 - 15);
        }
        name.setFillColor(sf::Color::Yellow);
        window->draw(name);
    }
}



// ------------------------------
// itemGenerator functions below.

std::unique_ptr<Item> itemGenerator::createEquipment(float x, float y, Player* player) { // Creates randomly an armor or a weapon for the item room.
    srand(time(NULL));
    int difficulty = player->GetDifficulty();
    int armorWeapon = (rand() % static_cast<int>(1 - 0 + 1));
    int quality = rand() % 2 + 0;
    std::string itemName;
    if(difficulty < 4){
        itemName = quality_[quality] + " " + material_[difficulty];
    }
    else {
        itemName = quality_[quality] + material_[3];
    }
    int equipmentValue = quality + difficulty + 1;
    sf::Vector2f v1(0.f, 0.f);
    if (armorWeapon == 0) {
        itemName += " Weapon";
        return std::make_unique<Weapon>(x, y, v1, itemName, player, equipmentValue);
    }
    else {
        itemName += " Armor";
        return std::make_unique<Armor>(x, y, v1, itemName, player, equipmentValue);
    }
}

std::unique_ptr<Item> itemGenerator::createConsumable(float x, float y, Player* player) { //At the moment this function can only create healing potions so the two lines are commented.
    //srand((unsigned int)time(NULL)); 
    //int random_cons = rand() % 1 + 0;
    sf::Vector2f v1(0.f, 0.f);
    return std::make_unique<HealingPotion>(x, y, v1, "HPotion", player, 0);
}