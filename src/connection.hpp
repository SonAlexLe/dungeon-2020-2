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
Connections become interactable as the room is cleared of monsters
*/
class Connection : public Entity {
public:
    Connection();

    Connection(float x, float y, std::string f, std::shared_ptr<Player> p);
    
    void update(sf::Time dt);

    //Moves the player to another room
    void traverse();

    void draw(sf::RenderWindow* window);

private:


    std::string facing_;

    sf::Texture texture_; 

    sf::Sprite sprite_;

    std::shared_ptr<Player> player_;
};

