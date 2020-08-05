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
    Game game;

    game.init();

    while(game.isRunning())
    {
        game.input();
        game.update();
        game.render();
    }
    game.clean();

}