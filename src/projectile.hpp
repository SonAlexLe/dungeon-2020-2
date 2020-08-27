#pragma once
#include "entity.hpp"

//a projectile fired by the player. Supports future enemies that would fire projectiles.
class Projectile: public Entity
{
    private:

    //damage depends on the weapon used
    int damage_;

    //whether a projectile was fired by an enemy or by the player
    bool hostile_;

    //whether a projectile is to be rendered & updated
    //set as false if a projectile has hit something
    bool active_;

    sf::Sprite sprite_;

    sf::Texture texture_;

    public:

    //initial velocity of projectile is arbitrarily [0, 0]
    Projectile() = delete;
    Projectile(sf::Vector2f location,sf::Vector2f velocity, int damage, bool hostile) :
    Entity(location.x,location.y,velocity), damage_(damage), hostile_(hostile), active_(true) {
        if (!texture_.loadFromFile("src/Sprites/game_texture.png")) {std::cout << "sprite error" << std::endl;}
        sprite_ = sf::Sprite(texture_,sf::IntRect(146,8,10,25));
        //rotate the projectile
        float angle = 0;
        if( velocity_.x == 0 && velocity_.y < 0) {angle = 0;}
        else{
            if( velocity_.x == 0 && velocity_.y > 0) {angle = 180;}
            else{
                //calculate the rotational angle from the velocity vector, convert from radians to degrees.
                if(velocity_.x < 0){angle += 180;}
                angle += 90 + std::atan(velocity_.y/velocity_.x) * (180.0/(2*std::acos(0.0)));
            }
        }
        sprite_.rotate(angle);
        sprite_.setScale(sf::Vector2f(2, 2));
    }

    void SetVelocity(sf::Vector2f velocity) { velocity_ = velocity; }
    sf::Vector2f& GetVelocity() { return velocity_; }

    bool isActive() {return active_;}
    void setActive(bool x) { active_ = x;}

    int GetDamage(){return damage_;}
    
    sf::Sprite GetSprite() {return sprite_;}

    void Draw(sf::RenderWindow* w) {
        sf::FloatRect p_rec = sprite_.getGlobalBounds();
        sf::RectangleShape p_box(sf::Vector2f(p_rec.width, p_rec.height));
        p_box.setOutlineThickness(0.5);
        p_box.setOutlineColor(sf::Color::Transparent);
        p_box.setFillColor(sf::Color::Transparent);
        p_box.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
        w->draw(p_box);
        sprite_.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
        w->draw(sprite_);
    }

    void update(sf::Time dt) {
        currPos_ += dt.asSeconds() * velocity_;
    }

};