//main game loop of the program
#include "config.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "game.hpp"
//#include "inventory.hpp"

#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "TEST GAME");
    Game game(&window);
    if(DEBUGGING){
        std::cout << "Window open" << std::endl;
    }
    game.init();
    long long n = 0;
    while(game.isRunning())
    {
        if(DEBUGGING){
            std::cout << n << std::endl;
            n++;
        }
        game.input();
        game.update();
        game.render();
    }
    game.clean();

}