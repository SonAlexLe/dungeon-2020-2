#include "game.hpp"

Game::Game(sf::RenderWindow *window) : difficulty_(0), window_(window) 
{
    //load the resources to be used
    if (!gamefont_.loadFromFile("src/sprites/arial.ttf"))
    {
        std::cout << "font error" << std::endl;
    }
    if(!gametexture_.loadFromFile("src/sprites/game_texture.png")){
        std::cout << "sprite error" << std::endl;
    }
    //Generate a new dungeon floor as the starting map
    std::shared_ptr<Room> room = std::make_shared<Room>();
    p1_ = std::make_shared<Player>(room, gametexture_);
    dungeon_ = std::make_shared<Map>(difficulty_, p1_);
    p1_->SetRoom(dungeon_->GetStartingRoom());

    //Create a player object and place them in the starting room of the map

    //TODO move this into map gen
    /*Orc* o = new Orc(100, 100, p1_);
    o->SetHP(0);
    p1_->GetRoom()->AddEnemy(o); */

    p1_->GetRoom()->AddEnemy(std::make_shared<Orc>(100, 100, p1_));
    //Create an inventory
    inventory_ = std::make_shared<Inventory>(p1_);
    //Start the dT timer
    clock_.restart();
    //Game is now running, moving to the main loop.
    isRunning_ = true;
}

Game::~Game(){}

void Game::input()
{
    //poll events until all are handled, this is done each frame
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
            case sf::Keyboard::E: // E key uses the held consumable.
                inventory_->useConsumable();
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
                    sf::Vector2f projectile_velocity(projectile_direction.x/vlength*projectilespeed,
                                                    projectile_direction.y/vlength*projectilespeed);
                    //create new projectile, the creation point is the middle of player instead of the top-left corner, the coefficient is 6 because graphics are scaled 3 times from the actual game logic.
                    p1_->GetRoom()->AddProjectile(std::make_shared<Projectile>(
                        sf::Vector2f(p1_->GetPosition().x + (p1_->GetSprite().getGlobalBounds().width/6),
                        p1_->GetPosition().y+ p1_->GetSprite().getGlobalBounds().height/6),
                        projectile_velocity, 1, false, gametexture_));
                    //set the player reload time, reload must finish before firing
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
                    }
                }
            }
            //if a projectile hits a wall, it is deactivated and no longer updated or drawn
            else{
                i->setActive(false);
            }
        }
        if (p1_->GetRoom()->IsClear()) {
            for(auto x : p1_->GetRoom()->GetConnections()) {
                x->update(elapsed);
            }
        }
        lastUpdate_ = time;
    }
    //go through all the active entities in the current room and move them up to their speed.
    //enemy AI should happen here
    
}
void Game::render()
{
    //clear the screen
    window_->clear(sf::Color::Black);

    //draw the room
    // sf::Sprite roomsprite(gametexture_, sf::IntRect(0,90,64,48));
    sf::Vector2f roomSize = p1_->GetRoom()->GetSize();
    sf::RectangleShape room(roomSize*3.f);
    room.setTexture(&gametexture_);
    room.setTextureRect(sf::IntRect(0,90,64,48));
    // room.setFillColor(sf::Color::White);
    // roomsprite.setScale(sf::Vector2f(6, 6));
    window_->draw(room);
    // window_->draw(roomsprite);
    
    //draw the player
    p1_->Draw(window_);
    int charsize = 20;
    int counter = 0;
    //draw all enemies with more than 0hp
    for(auto i : p1_->GetRoom()->GetEnemies()) { 
        if (i->isActive()) {
            i->Draw(window_);
            std::stringstream ss;
            ss << (dynamic_cast<Orc*>(i.get()) ? "Orc" : (dynamic_cast<Orge*>(i.get()) ? "Orge" : "Boss")) << " HP: " << i->GetHP();
            sf::Text hp;
            hp.setFont(gamefont_);
            hp.setString(ss.str());
            hp.setCharacterSize(charsize);
            auto bounds = hp.getGlobalBounds();
            hp.setPosition(roomSize.x*3-bounds.width-10,2+(charsize+5)*counter++);
            hp.setFillColor(sf::Color::Yellow);
            window_->draw(hp);
        }
    }

    //draw all active projectiles
    for(auto x : p1_->GetRoom()->GetProjectiles()){
        if(x->isActive()){
            x->Draw(window_);
        }
    }
    if (p1_->GetRoom()->IsClear()) {
        for(auto x : p1_->GetRoom()->GetConnections()) {
        x->draw(window_);
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
    //generate attack & defense values on screen
    std::stringstream ss3;
    ss3 << "ATK: " << inventory_->getDmgValue();
    sf::Text ATK;
    ATK.setFont(gamefont_);
    ATK.setString(ss3.str());
    ATK.setCharacterSize(25);
    ATK.setFillColor(sf::Color::Red);
    ATK.setStyle(sf::Text::Bold);
    ATK.setPosition(0, 60);
    window_->draw(ATK);
    //---DEF
    std::stringstream ss4;
    ss4 << "DEF: " << inventory_->getArmorValue();
    sf::Text DEF;
    DEF.setFont(gamefont_);
    DEF.setString(ss4.str());
    DEF.setCharacterSize(25);
    DEF.setFillColor(sf::Color::Yellow);
    DEF.setStyle(sf::Text::Bold);
    DEF.setPosition(0, 90);
    window_->draw(DEF);
    

    //GAME OVER TEXT FOR WHEN THE PLAYER DIES
    if(p1_->GetHP() <= 0){
        sf::Text gameover;
        gameover.setFont(gamefont_);
        gameover.setCharacterSize(100);
        gameover.setString("YOU DIE");
        gameover.setFillColor(sf::Color::Red);
        gameover.setStyle(sf::Text::Underlined | sf::Text::Bold);
        gameover.setPosition(sf::Vector2f(window_->getSize().x/2 - gameover.getGlobalBounds().width/2, window_->getSize().y/2 - gameover.getGlobalBounds().height/2));
        window_->draw(gameover);
    }

    //display graphics
    window_->display();
}

void Game::clean()
{
    window_->close();
    //memory cleanup on game close, will be created later...
}