#pragma once
#include "entity.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "entity.hpp"
#include "player.hpp"


/*Each connection object functions as a doorway to a different room or new map 
Connections inherit the Entity class, 
on top of that each connection has a reference to another connection and a method for traversing from one connection to the other.
By default connections are locked and need to be unlocked by key or by clearing the room (subject to change)
*/
class Connection : public Entity {
public:
    Connection();

    Connection(float x, float y, std::string f, std::shared_ptr<Player> p);
    
    void unlock();

    const std::string GetSpriteName() const; 

    void update(sf::Time dt);

    void load();

    /*WIP. Maybe should take the player as a parameter or is called when a connection and a player collide.
     Also needs to place the player on the correct spot after traversing. (Tried to connect connections together) */
    void traverse();

    void draw(sf::RenderWindow* window);

private:

    bool locked_;

    std::string facing_;

    sf::Texture texture_; 

    sf::Sprite sprite_;

    std::shared_ptr<Player> player_;
};