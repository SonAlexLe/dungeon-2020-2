#include "game.hpp"

Game::Game(sf::RenderWindow *window) : difficulty_(0), window_(window) 
{
    //Generate a new dungeon floor as the starting map
    dungeon_ = new Map(difficulty_);
    //Create a player object and place them in the starting room of the map
    p1_ = new Player(dungeon_->GetStartingRoom());

    //TODO move this into map gen
    p1_->GetRoom()->AddEnemy(new Orc(100, 100, p1_));
    p1_->GetRoom()->AddEnemy(new Orge(0, 0, p1_));
    //Create an inventory
    inventory_ = new Inventory(p1_);
    //load the font to be used for in-game text
    if (!gamefont_.loadFromFile("src/sprites/arial.ttf"))
    {
        std::cout << "font error" << std::endl;
    }
    //Start the dT timer
    clock_.restart();
    //Game is now running, moving to the main loop.
    isRunning_ = true;
}
Game::~Game(){}

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
            //Handling keyboard input. Pressing down and releasing a key are treated as separate events.
            //WASD control the movement, toggling the player acceleration in a given direction on or off.
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
        //Clicking the left mouse button fires a projectile towards the direction of the mouse. 
                if(event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    if(p1_->GetReload() == 0){
                        float projectilespeed = 150;
                        //calculate the direction of the projectile with the linear combination of the mouse and player location vectors. 
                        sf::Vector2f projectile_direction = p1_->GetPosition() - sf::Vector2f(sf::Mouse::getPosition(*window_).x/3 ,sf::Mouse::getPosition(*window_).y/3);
                        //calculate speed with the pythagoran theorem
                        float vlength = -1 * std::sqrt(projectile_direction.x*projectile_direction.x + projectile_direction.y * projectile_direction.y);
                        //velocity = unit direction vector * speed
                        sf::Vector2f projectile_velocity(projectile_direction.x/vlength*projectilespeed,projectile_direction.y/vlength*projectilespeed);
                        //create new projectile
                        p1_->GetRoom()->AddProjectile(new Projectile(p1_->GetPosition(),projectile_velocity, 1, false));
                        //set the player reload time, reload muat finish before firing
                        p1_->Attack();
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
    if(p1_->GetHP() > 0){
        //calculate time since last update
        sf::Time time = clock_.getElapsedTime();
        sf::Time elapsed = time - lastUpdate_;

        //update player
        p1_->update(elapsed);
        //update all enemies within the active room
        for(auto i : p1_->GetRoom()->GetEnemies()) {
            if(i->isActive())
                {i->update(elapsed);}
        }
        //update all projectiles, bounds is used for checking projectile collision with walls
        sf::Vector2f bounds = p1_->GetRoom()->GetSize();
    
        for(auto i : p1_->GetRoom()->GetProjectiles()){
            sf::Vector2f Ppos = i->GetPosition();
        
            if(Ppos.x >= 0 && Ppos.y >= 0 && Ppos.x < bounds.x && Ppos.y < bounds.y && i->isActive()){
                i->update(elapsed);
            
                for(auto j : p1_->GetRoom()->GetEnemies()){
                
                //check projectile collision with an enemy. projectile disappears on hitting an enemy.
                    if(j->GetHP()>0 && i->GetSprite().getGlobalBounds().intersects(j->GetSprite().getGlobalBounds())){
                        i->setActive(false);
                    //calculate new hp for damaged enemy
                        j->SetHP(j->GetHP()-i->GetDamage());
                        std::cout<<j->GetHP()<<std::endl;
                    }
                }
            }
            //if a projectile hits a wall, it is deactivated and no longer updated or drawn
            else{
                i->setActive(false);
            }
        }
        lastUpdate_ = time;
    }
    
}
void Game::render()
{
    //clear the screen
    window_->clear(sf::Color::Black);

    //create the graphics representing the current room
    sf::Vector2f roomSize = p1_->GetRoom()->GetSize();
    sf::RectangleShape room(sf::Vector2f(roomSize.x*3,roomSize.y*3));
    room.setFillColor(sf::Color::White);
    window_->draw(room);
    
    //draw the player
    p1_->Draw(window_);

    //draw all enemies with more than 0hp
    for(auto i : p1_->GetRoom()->GetEnemies()) { 
        if (i->isActive()) {i->Draw(window_);}
    }

    //draw all active projectiles
    for(auto x : p1_->GetRoom()->GetProjectiles()){
        if(x->isActive()){
            x->Draw(window_);
        }
    }
    
    //generate and draw score & hp text on screen
    std::stringstream ss;
    ss<< "Score: " << p1_->GetScore();
    sf::Text score;
    score.setFont(gamefont_);
    score.setString(ss.str());
    score.setCharacterSize(25);
    score.setFillColor(sf::Color::Blue);
    score.setStyle(sf::Text::Underlined);
    window_->draw(score);
    std::stringstream ss2;
    ss2 << "HP: "<< p1_->GetHP();
    sf::Text hp;
    hp.setFont(gamefont_);
    hp.setString(ss2.str());
    hp.setCharacterSize(25);
    hp.setFillColor(sf::Color::Green);
    hp.setStyle(sf::Text::Bold);
    hp.setPosition(0,30);
    window_->draw(hp);
    //display graphics

    //GAME OVER TEXT FOR WHEN HP = 0
    if(p1_->GetHP()<= 0){
        sf::Text gameover;
        gameover.setFont(gamefont_);
        gameover.setCharacterSize(100);
        gameover.setString("GAME OVER!");
        gameover.setFillColor(sf::Color::Red);
        gameover.setStyle(sf::Text::Underlined | sf::Text::Bold);
        gameover.setPosition(sf::Vector2f(window_->getSize().x/2 - gameover.getGlobalBounds().width/2, window_->getSize().y/2 - gameover.getGlobalBounds().height/2));
        window_->draw(gameover);
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