//main game loop of the program
#include "config.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "entity.hpp"
#include "map.hpp"
#include "player.hpp"
#include "inventory.hpp"

#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 900), "TEST GAME");
    Game game(&window);
    while(game.isRunning())
    {
        game.input();
        game.update();
        game.render();
    }
    game.clean();

}