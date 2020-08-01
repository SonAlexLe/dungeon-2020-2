#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "room.hpp"

class Room;

class Entity
{
public:

    Entity();

    Entity(double x, double y);

    virtual ~Entity();

    void update(sf::Time dt);

    void SetRoom(Room* room);

    Room* GetRoom();

    sf::Vector2f GetPosition();

    void SetPosition(sf::Vector2f pos);

protected:

    sf::Vector2f velocity_;

    sf::Vector2f currPos_;

    Room* room_;

};