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
    sf::RenderWindow window(sf::VideoMode(1280, 720), "TEST GAME");
    Game game(&window);
    while(game.isRunning())
    {
        game.input();
        std::cout << "input handling succesful" << std::endl;
        //game.update();
        std::cout << "game objects updated" << std::endl;
        //game.render();
    }
    game.clean();

}