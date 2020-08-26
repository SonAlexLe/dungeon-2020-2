#include "game.hpp"
#include <list>
Game::Game(sf::RenderWindow *window) : score_(0), difficulty_(0), window_(window) 
{
    dungeon_ = new Map(difficulty_);
    p1_ = new Player(dungeon_->GetStartingRoom());
    p1_->GetRoom()->AddEnemy(new Orc(100, 100, p1_));
    p1_->GetRoom()->AddEnemy(new Orge(0, 0, p1_));
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
                        sf::Vector2f projectile_direction = p1_->GetPosition() - sf::Vector2f(sf::Mouse::getPosition(*window_).x/3 ,sf::Mouse::getPosition(*window_).y/3);
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

void Game::update()
{
    sf::Time time = clock_.getElapsedTime();
    sf::Time elapsed = time - lastUpdate_;
    p1_->update(elapsed);
    for(auto i : p1_->GetRoom()->GetEnemies()) {
        i->update(elapsed);
        // if(i->GetHP() <= 0) {
        //     score_ += 1;
        //     delete i;
        // }
    }
    sf::Vector2f bounds = p1_->GetRoom()->GetSize();
    for(auto i : p1_->GetRoom()->GetProjectiles()){
        sf::Vector2f Ppos = i->GetPosition();
        if(Ppos.x >= 0 && Ppos.y >= 0 && Ppos.x < bounds.x && Ppos.y < bounds.y && i->isActive()){
            i->update(elapsed);
            for(auto j : p1_->GetRoom()->GetEnemies()){
                if(i->GetSprite().getGlobalBounds().intersects(j->GetSprite().getGlobalBounds())){
                    i->setActive(false);
                    j->SetHP(j->GetHP()-i->GetDamage());
                    std::cout<<j->GetHP()<<std::endl;
                }
            }
        }
        else{
            i->setActive(false);
        }
    }
    //go through all the active entities in the current room and move them up to their speed.
    //enemy AI should happen here
    
    //check for entity & projectile collision
    lastUpdate_ = time;
}
void Game::render()
{
    window_->clear(sf::Color::Black);
    //placeholder
    sf::Vector2f roomSize = p1_->GetRoom()->GetSize();
    sf::RectangleShape room(sf::Vector2f(roomSize.x*3,roomSize.y*3));
    room.setFillColor(sf::Color::White);
    window_->draw(room);
    // p1_->GetSprite().setPosition(sf::Vector2f(p1_->GetPosition().x*3,p1_->GetPosition().y*3));
    // window_->draw(p1_->GetSprite());
    p1_->Draw(window_);
    for(auto i : p1_->GetRoom()->GetEnemies()) { 
        // i->GetSprite().setPosition(sf::Vector2f(i->GetPosition().x*3,i->GetPosition().y*3));
        // window_->draw(i->GetSprite());
        i->Draw(window_);
    }
    for(auto x : p1_->GetRoom()->GetProjectiles()){
        if(x->isActive()){
            x->Draw(window_);
        }
    }
    window_->display();
}

void Game::clean()
{
    delete p1_;
    delete inventory_;
    delete dungeon_;
    window_->close();
    //memory cleanup on game close, will be created later...
}