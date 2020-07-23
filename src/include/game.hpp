#pragma once
#include "map.hpp"
#include "entity.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class   Game
{
public:
    Game();
    //Game cannot be copied
    Game(const Game&)   =   delete;
    Game    operator=(const Game&) =   delete;
    ~Game();

    void     init();
    void    input();
    void    update();
    void    render();
    void    clean();
    bool    isRunning();


private:
    bool    isRunning_;
     
    int score_;
    int difficulty_;
    sf::RenderWindow    *window_;
    Map dungeon_;
    Player  p1_;
    //add possible additional player...
};