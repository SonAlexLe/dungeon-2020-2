#pragma once
#include <map>
#include "map.hpp"
#include "entity.hpp"
#include "player.hpp"
#include "inventory.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

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

    int score_;
    int difficulty_;

    sf::RenderWindow* window_;
    Map dungeon_;
    Player* p1_;
    Inventory* inventory_;
    sf::Clock clock_;
    sf::Time lastUpdate_;
    //add possible additional player...
};