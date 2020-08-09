#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "room.hpp"
#include <string>

class Entity
{
public:

    Entity();

    Entity(float x, float y, sf::Vector2f velocity);

    virtual ~Entity();

    virtual void update(sf::Time dt) =0;

    virtual const std::string GetSpriteName() const =0;

    virtual void load();

    void SetRoom(Room* room);

    Room* GetRoom();

    sf::Vector2f& GetPosition();

    void SetPosition(sf::Vector2f pos);

protected:

    sf::Vector2f currPos_;

    sf::Vector2f velocity_;

    Room* room_;

};