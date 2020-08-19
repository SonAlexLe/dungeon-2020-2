#pragma once
#include "monster.hpp"

class Orc : public Monster
{
    public:
    Orc() = delete;
    Orc(Room* room);
    void update(sf::Time dt);
};