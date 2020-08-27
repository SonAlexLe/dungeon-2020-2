//main game loop of the program
#include "config.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "entity.hpp"
#include "map.hpp"
#include "player.hpp"
#include "inventory.hpp"
#include <memory>

#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(950, 950), "Dungeons I");
    //create and initialize game object
    Game game(&window);

    while(game.isRunning())
    {
        //handle player input
        game.input();
        //update game entities
        game.update();
        //draw graphics
        game.render();
    }
    //clean up memory
    game.clean();

}