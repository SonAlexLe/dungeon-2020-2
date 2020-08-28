#pragma once
#include "entity.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "entity.hpp"
#include "player.hpp"


/*Each connection object functions as a doorway to a different room
The connections facing determines to which of the rooms neighbors the player is transported to.
By default connections are locked and need to be unlocked by clearing the room 
*/
class Connection : public Entity {
public:
    Connection();

    Connection(float x, float y, std::string f, std::shared_ptr<Player> p);
    
    void unlock();

    const std::string GetSpriteName() const; 

    void update(sf::Time dt);


    //Moves the player to another room
    void traverse();

    void draw(sf::RenderWindow* window);

private:

    bool locked_;

    std::string facing_;

    sf::Texture texture_; 

    sf::Sprite sprite_;

    std::shared_ptr<Player> player_;
};

