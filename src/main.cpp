//main game loop of the program
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "entity.hpp"
#include "map.hpp"
#include "player.hpp"
#include "inventory.hpp"




int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "TEST GAME");
    Game game(&window);

    game.init();

    while(game.isRunning())
    {
        game.input();
        game.update();
        game.render();
    }
    game.clean();

}