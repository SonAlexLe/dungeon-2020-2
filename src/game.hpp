#pragma once
#include <vector>
#include "map.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "inventory.hpp"
#include "monster.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <list>
#include <sstream>
#include <memory>
/* 
** The game class is a container class for all the contents of the game.
** It handles entity updating, input and graphics.
** The same instance of Game is kept around until the program is closed.
*/

class Game
{
public:
    Game(sf::RenderWindow*);
    //Game cannot be copied
    Game(const Game&) = delete;
    Game operator=(const Game&) = delete;
    ~Game();
    
    void init();
    void input();
    void update();
    void render();
    void clean();
    bool isRunning() {
        return isRunning_;
    }


private:
    bool isRunning_;
    int difficulty_;

    sf::RenderWindow* window_;
    sf::Font gamefont_;
    sf::Texture gametexture_;

//for determining deltatime
    sf::Clock clock_;
    sf::Time lastUpdate_;

    std::shared_ptr<Map> dungeon_;

    std::shared_ptr<Player> p1_;
    std::shared_ptr<Inventory> inventory_;
};