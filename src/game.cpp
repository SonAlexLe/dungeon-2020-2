#include "game.hpp"
#include <list>
Game::Game(sf::RenderWindow *window) : score_(0), difficulty_(0), window_(window) 
{
    dungeon_ = Map(difficulty_);
    p1_ = new Player(dungeon_.GetStartingRoom());
    p1_->GetRoom()->AddEnemy(new Orc(100, 100, p1_));
    inventory_ = new Inventory(p1_);
    clock_.restart();
    isRunning_ = true;
}
Game::~Game(){}


void Game::init() //might be redundant
{
    //game should also open all required sprites to memory, throw errors if files are not found.
}


void Game::input()
{
    sf::Event event;
    while (window_->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            //handle window close
                isRunning_ = false;
                break;

        case sf::Event::KeyPressed:
            //pass keyboard input to the player object, needs to be updated if second player is implemented
            //note, the event only handles key down / key up, meaning that pressing a key must start the player moving
            //until the key is released, ie. the key up event is passed to the player!! 
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    p1_->accUp(true);
                    break;
                case sf::Keyboard::A:
                    p1_->accLeft(true);
                    break;
                case sf::Keyboard::S:
                    p1_->accDown(true);
                    break;
                case sf::Keyboard::D:
                    p1_->accRight(true);
                    break;
                default:
                //could add other keys here...
                    break;
                }
                break;

        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                p1_->accUp(false);
                break;
            case sf::Keyboard::A:
                p1_->accLeft(false);
                break;
            case sf::Keyboard::S:
                p1_->accDown(false);
                break;
            case sf::Keyboard::D:
                p1_->accRight(false);
                break;
            default:
            //could add other keys here...
                break;
            }
            break;

        case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Button::Left) 
                {
                    if(p1_->GetReload() == 0){
                        float projectilespeed = 50;
                        std::cout << "shooting" << std::endl;
                        sf::Vector2f projectile_direction = p1_->GetPosition() - sf::Vector2f(sf::Mouse::getPosition(*window_).x ,sf::Mouse::getPosition(*window_).y);
                        float vlength = -1 * std::sqrt(projectile_direction.x*projectile_direction.x + projectile_direction.y * projectile_direction.y);
                        sf::Vector2f projectile_velocity(projectile_direction.x/vlength*projectilespeed,projectile_direction.y/vlength*projectilespeed);
                        p1_->GetRoom()->AddProjectile(new Projectile(p1_->GetPosition(),projectile_velocity, 1, false));
                        p1_->Attack();
                        std::cout << "pew "<<p1_->GetRoom()->GetProjectiles().size() << std::endl;
                    }
                }
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
    p1_->update(elapsed);
    /*for(auto i : p1_->GetRoom()->GetEnemies())
    {
        i->update(elapsed);
    }*/
    sf::Vector2f bounds = p1_->GetRoom()->GetSize();
    for(auto i : p1_->GetRoom()->GetProjectiles()){
        sf::Vector2f pPos = i->GetPosition();
        //commented for testing
        /*if(pPos.x < 0 || pPos.x > bounds.x || pPos.y < 0 ||pPos.y > bounds.y){
            delete i;
        }*/
    }
    for(auto i : p1_->GetRoom()->GetProjectiles())
    {
        i->update(elapsed);
    }
    

    //go through all the active entities in the current room and move them up to their speed.
    //enemy AI should happen here
    for(auto i : p1_->GetRoom()->GetEnemies()) {
        i->update(elapsed);
    }
    //check for entity & projectile collision
    //

    lastUpdate_ = time;
}
void Game::render()
{
    window_->clear(sf::Color::Black);
    double scale = std::min(window_->getSize().y/1080,window_->getSize().x/1900);
    //placeholder
    sf::Vector2f roomSize = p1_->GetRoom()->GetSize();
    //if(DEBUGGING){std::cout << roomSize.x << " " << roomSize.y << std::endl;}
    sf::RectangleShape room(roomSize);
    room.setFillColor(sf::Color::White);
    sf::CircleShape player(10);
    player.setFillColor(sf::Color(100, 250, 50));
    player.setPosition(p1_->GetPosition());
    window_->draw(room);
    window_->draw(player);
    for(auto i : p1_->GetRoom()->GetEnemies()) {
        sf::CircleShape monster(5);
        monster.setFillColor(sf::Color(250, 50, 100));
        monster.setPosition(i->GetPosition());
        window_->draw(monster);
    }
    for(auto x : p1_->GetRoom()->GetProjectiles()){
        sf::CircleShape pew(x->GetDamage());
        pew.setFillColor(sf::Color::Blue);
        pew.setPosition(x->GetPosition());
        window_->draw(pew);
    }
    window_->display();
}

void Game::clean()
{
    window_->close();
    //memory cleanup on game close, will be created later...
}
