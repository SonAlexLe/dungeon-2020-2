#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>

class Room;

/*Base class for all things inside a room. Handles the 2d location and movement of an object.
**All other classes inherit from this class.
*/

class Entity
{
public:

    Entity();
    Entity(float x, float y, sf::Vector2f velocity);
    virtual ~Entity();

    virtual void update(sf::Time dt);

    virtual const std::string GetSpriteName() const =0;
    
    sf::Vector2f& GetPosition();
    sf::Vector2f& GetVelocity();

    void SetPosition(sf::Vector2f pos);


protected:

    sf::Vector2f currPos_;
    sf::Vector2f velocity_;

};