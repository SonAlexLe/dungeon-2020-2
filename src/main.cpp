//main game loop of the program
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
    sf::RenderWindow window(sf::VideoMode(800, 600), "TEST GAME");
    Game game(&window);
    std::cout << "Window open" << std::endl;
    game.init();
    int n = 0;
    while(game.isRunning())
    {
        std::cout << n << std::endl;
        game.input();
        game.update();
        game.render();
        n++;
    }
    game.clean();

}