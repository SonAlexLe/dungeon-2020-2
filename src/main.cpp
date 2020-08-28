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
    sf::RenderWindow window(sf::VideoMode(900, 900), "Dungeons 1.5");
    window.setPosition(sf::Vector2i(450, 50));
    sf::Music music;
    if (!music.openFromFile("src/sprites/main.ogg"))
    {
        std::cout << "music error" << std::endl;
    }
    //create and initialize game object
    Game game(&window);
    music.play();
    music.setLoop(true);
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