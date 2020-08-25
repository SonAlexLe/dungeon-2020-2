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
    /** Updates the Entity after each game loop
     * 
     * @param dt the time elapsed after the last loop
     */ 
    virtual void update(sf::Time dt) =0;

    sf::Vector2f& GetPosition();

    void SetPosition(sf::Vector2f pos);

    void SetRoom(Room* room);

    Room* GetRoom();

protected:

    sf::Vector2f currPos_;

    Room* room_;

};