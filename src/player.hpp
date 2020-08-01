#pragma once
#include "entity.hpp"

//placeholder, please include empty constructor for testing purposes

class Player : public Entity
{
public:
    Player();
    Player(double x, double y);
    void input(sf::Event::KeyEvent e, bool cond);
    void click(sf::Event e, bool cond);
private:
    int a_;
};