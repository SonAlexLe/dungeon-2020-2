#pragma once
#include "map.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "inventory.hpp"
#include "monster.hpp"
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

    bool checkBounds(Entity *);
    
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
    Monster* monst_; // for testing
    Inventory* inventory_;
    sf::Clock clock_;
    sf::Time lastUpdate_;
    //add possible additional player...
};