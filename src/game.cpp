#include "game.hpp"
#include "graphics.cpp"

Game::Game()
{}
Game::~Game()
{}

void Game::init() //add arguments?? 
{
    //game should also open all required sprites to memory, throw errors if files are not found.
    sf::RenderWindow window(sf::VideoMode(800, 600), "TEST GAME");
    dungeon_ = Map();
    score_ = 0;
    difficulty_ = 0;
    p1_ = Player();
    window_ = &window;
    clock_.restart();
}

void Game::input()
{
    sf::Event event;
    while(window_->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            //handle window close
                window_->close();
                isRunning_ = false;
                break;

            case sf::Event::KeyPressed: 
            //pass keyboard input to the player object, needs to be updated if second player is implemented
            //note, the event only handles key down / key up, meaning that pressing a key must start the player moving
            //until the key is released, ie. the key up event is passed to the player!! 
                if(event.key.code == sf::Keyboard::Escape)
                {
                    //code to pause the game
                    //pausing should stop the game from rendering and stop the game logic, making only a pause menu render.
                    //clicking continue in game or pressing esc again resumes the game
                }
                else
                {
                    p1_.input(event.key);
                }
                break;

            case sf::Event::KeyReleased:
                p1_.input(event.key);
                break;

            case sf::Event::MouseButtonPressed:
                p1_.click(event);
                break;

            case sf::Event::MouseButtonReleased:
                p1_.release(event);
                break;

            default:
                break;
        }
    }
}

void    Game::update()
{
    for(auto i : p1_.GetRoom().GetDenizens())
    {
        i.update(clock_.getElapsedTime() - lastUpdate_);
    }
    p1_.update(clock_.getElapsedTime() - lastUpdate_);
    
    lastUpdate_ = clock_.getElapsedTime();

    //go through all the active entities in the current room and move them up to their speed.
    //enemy AI should happen here
    //check fore entity & projectile collision
    //
} 
void Game::render()
{
    window_->clear();

    /* draw the background, room, player and all other entities */ 
    window_->display();
}

void Game::clean()
{
    //memory cleanup on game close, will be created later...
}
