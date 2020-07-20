#include "game.hpp"

Game::Game()
{}
Game::~Game()
{}

void Game::init() //add arguments 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    dungeon_ = Map();
    score_ = 0;
    p1_ = Player();
    window_ = window;


}

void    Game::input()
{
    sf::Event event;
    while   window_.pollEvent(event)
    {
        switch(event)
        {
            case    sf::Event::Closed:
                window_.close();
                isRunning_  =    false;
                break;
            default:
                
        }
    }
}

void    Game::update()
{}

void    Game::render()
{}

void    Game::clean()
{}
