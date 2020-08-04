#pragma once
#include "weapon.hpp"
#include "player.hpp"

//should be abstract for future subtypes, right now is concrete
class Projectile : public Weapon
{
    private:

    sf::Vector2f velocity_;

    public:

    //initial velocity of projectile is arbitrarily [0, 0]
    Projectile() : Weapon(0, 0, "projectile", 1, nullptr, 10) {}
    Projectile(float x, float y, const std::string& name, const int type, Player* player,  int value) :
    Weapon(x, y, name, type, player, value) { velocity_ = sf::Vector2f(0, 0); }

    void SetVelocity(sf::Vector2f velocity) { velocity_ = velocity; }

    sf::Vector2f& GetVelocity() { return velocity_; }

    const std::string GetSpriteName() const { return "projectile.png"; }

};