#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>

class Room;

/** Base class of all entities that exist in a room.
 *  An Entity knows its own current room and current position
 */ 
class Entity
{
public:

    Entity();

    Entity(float x, float y);
    
    /** Constructor of Entity
     * 
     * @param x the x-coord
     * @param y the y-coord
     * @param room the initial room
     */ 
    Entity(float x, float y, Room* room);

    virtual ~Entity();

    virtual void update(sf::Time dt);

    virtual const std::string GetSpriteName() const =0;

    sf::Vector2f& GetPosition();

    sf::Vector2f GetVelocity() const;

    void SetPosition(sf::Vector2f pos);

    void SetRoom(Room* room);

    Room* GetRoom();

protected:

    sf::Vector2f currPos_;

    Room* room_;

};