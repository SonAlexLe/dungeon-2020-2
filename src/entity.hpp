#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>

class Room;

class Entity
{
public:

    Entity();
    
    /** Constructor of Entity
     * 
     * @param x the x-coord
     * @param y the y-coord
     */ 
    Entity(float x, float y);

    virtual ~Entity();
    /** Updates the Entity after each game loop
     * 
     * @param dt the time elapsed after the last loop
     */ 
    virtual void update(sf::Time dt) =0;

    virtual const std::string GetSpriteName() const =0;

    virtual void load() =0;

    sf::Vector2f& GetPosition();

    void SetPosition(sf::Vector2f pos);

    void SetRoom(Room* room);

    Room* GetRoom();

protected:

    sf::Vector2f currPos_;

    Room* room_;

};