#pragma once
#include "entity.hpp"

//should be abstract for future subtypes, right now is concrete
class Projectile: public Entity
{
    private:

    int damage_;

    bool hostile_;

    bool active_;

    public:

    //initial velocity of projectile is arbitrarily [0, 0]
    Projectile() = delete;
    Projectile(sf::Vector2f location,sf::Vector2f velocity, int damage, bool hostile) :
    Entity(location.x,location.y,velocity), damage_(damage), hostile_(hostile), active_(true) {}

    void SetVelocity(sf::Vector2f velocity) { velocity_ = velocity; }

    sf::Vector2f& GetVelocity() { return velocity_; }

    bool isActive() {return active_;}

    void setActive(bool x) { active_ = x;}

    int GetDamage(){return damage_;}

    const std::string GetSpriteName() const { return "projectile.png"; }

    void update(sf::Time dt) {
        currPos_ += dt.asSeconds() * velocity_;
    }

};