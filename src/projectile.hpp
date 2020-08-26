#pragma once
#include "entity.hpp"

//should be abstract for future subtypes, right now is concrete
class Projectile: public Entity
{
    private:

    int damage_;

    bool hostile_;

    bool active_;

    sf::Sprite sprite_;

    sf::Texture texture_;

    public:

    //initial velocity of projectile is arbitrarily [0, 0]
    Projectile() = delete;
    Projectile(sf::Vector2f location,sf::Vector2f velocity, int damage, bool hostile) :
    Entity(location.x,location.y,velocity), damage_(damage), hostile_(hostile), active_(true) {
        if (!texture_.loadFromFile("src/Sprites/staggerbot.png")) std::cout << "sprite error" << std::endl;
        sprite_.setTexture(texture_);
        sprite_.setScale(sf::Vector2f(0.04f, 0.04f));
    }

    void SetVelocity(sf::Vector2f velocity) { velocity_ = velocity; }

    sf::Vector2f& GetVelocity() { return velocity_; }

    bool isActive() {return active_;}

    void setActive(bool x) { active_ = x;}

    int GetDamage(){return damage_;}

    const std::string GetSpriteName() const { return "projectile.png"; }

    sf::Sprite GetSprite() {return sprite_;}

    void Draw(sf::RenderWindow* w) {
        sf::FloatRect p_rec = sprite_.getGlobalBounds();
        sf::RectangleShape p_box(sf::Vector2f(p_rec.width, p_rec.height));
        p_box.setOutlineThickness(0.5);
        p_box.setOutlineColor(sf::Color::Red);
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