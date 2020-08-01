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
    dungeon_ = Map(0);
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
                    p1_.input(event.key,true);
                }
                break;

            case sf::Event::KeyReleased:
                p1_.input(event.key,false);
                break;

            case sf::Event::MouseButtonPressed:
                p1_.click(event,true);
                break;

            case sf::Event::MouseButtonReleased:
                p1_.click(event,false);
                break;

            default:
                break;
        }
    }
}

void    Game::update()
{
    sf::Time time = clock_.getElapsedTime();
    sf::Time elapsed = time - lastUpdate_;
    p1_.update(elapsed);
    for(auto i : p1_.GetRoom()->GetEnemies())
    {
        i.update(elapsed);
    }
    for(auto i : p1_.GetRoom()->GetProjectiles())
    {
        i.update(elapsed);
    }

    lastUpdate_ = time;

    //go through all the active entities in the current room and move them up to their speed.
    //enemy AI should happen here
    //check fore entity & projectile collision
    //
} 
void Game::render()
{
    window_->clear(sf::Color::Black);
    double scale = std::min(window_->getSize().y/1080,window_->getSize().x/1900);
    //placeholder
    sf::RectangleShape room(sf::Vector2f(p1_.GetRoom().GetWidth()*scale*1900, p1_.GetRoom().GetHeight()*scale*1080));
    sf::CircleShape player(10);
    player.setPosition(p1_.GetPosition());
    
    /* draw the background, room, player and all other entities */ 
    window_->display();
}

void Game::clean()
{
    //memory cleanup on game close, will be created later...
}
