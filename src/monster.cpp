#include "monster.hpp"
#define ORC_SPEED 30.f
#define ORGE_SPEED 5.f
#define ORC_HP 5
#define ORGE_HP 10
#define BOSS_HP 15
#define BOSS_SPEED 100.f
#define BOSS_DECCEL 50.f
#define BOSS_COOLDOWN 1.5
#define BOSS_RAGE_LIMIT 0.2

Monster::Monster() {}

/** A constructor for a monster
 * @param x x-coord
 * @param y y-coord
 * @param velocity initial velocity
 * @param hp initial hit points
 * @param p the player shared vector
 */
Monster::Monster(float x, float y, sf::Vector2f velocity, int hp, Player* p)
    : Entity(x, y, velocity), hp_(hp), p_(p), active_(true) {}

//renders a monster onscreen
void Monster::Draw(sf::RenderWindow* w, sf::Font& f, sf::Color c) {
    sf::Vector2f roomSize = p_->GetRoom()->GetSize();
    sf::FloatRect m_rec = sprite_.getGlobalBounds();
    sf::RectangleShape m_box(sf::Vector2f(m_rec.width, m_rec.height));
    m_box.setOutlineThickness(2);
    m_box.setOutlineColor(c);
    m_box.setFillColor(sf::Color::Transparent);
    m_box.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(m_box);
    sprite_.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(sprite_);
    std::stringstream ss;
    ss << " HP: " << this->GetHP();
    sf::Text hp;
    hp.setFont(f);
    hp.setString(ss.str());
    hp.setCharacterSize(12);
    auto bounds = hp.getGlobalBounds();
    hp.setPosition(currPos_.x*3, currPos_.y*3-12);
    hp.setFillColor(sf::Color::Yellow);
    w->draw(hp);
}

//Getters and setters for managing members
void Monster::SetHP(int hp) { hp_ = hp; }
int Monster::GetHP() { return hp_; }

void Monster::SetPlayer(Player* p) { p_ = p; }
Player* Monster::GetPlayer() { return p_; }

sf::Sprite& Monster::GetSprite() { return sprite_; }

//if a monster is not active (not dead), it won't be drawn
bool Monster::isActive() { return active_; }
void Monster::setActive(bool x) {active_ = x;}

//No part of a monster's sprite should be outside of the room on spawn
void Monster::AdjustSpawn() {
    auto bounds = sprite_.getGlobalBounds();
    if (currPos_.x+bounds.width/3 > 300)
        currPos_ = sf::Vector2f(300-bounds.width/3, currPos_.y);
    if (currPos_.y+bounds.height/3 > 300)
        currPos_ = sf::Vector2f(currPos_.x, 300-bounds.height/3);
}

//subclass orc, patrols from one corner to the opposite one.
Orc::Orc(float x, float y, Player* p)
    : Monster(x, y, sf::Vector2f(ORC_SPEED, ORC_SPEED), ORC_HP, p)
{
    sprite_ = sf::Sprite(p->GetTexture(), sf::IntRect(32,160,16,16));
    sprite_.setScale(sf::Vector2f(2, 2));
    AdjustSpawn();
}

//determines the behavior of an Orc
void Orc::update(sf::Time dt) {
    auto bounds = sprite_.getGlobalBounds();
    //checks collision with player
    if (!p_->CanDie() || !bounds.intersects(p_->GetSprite().getGlobalBounds())) {
        if(currPos_.x+bounds.width/3 > p_->GetRoom()->GetWidth()-1 || currPos_.y+bounds.height/3 > p_->GetRoom()->GetHeight()-1)
            velocity_ = sf::Vector2f(-ORC_SPEED, -ORC_SPEED);
        else if(currPos_.x < 1 || currPos_.y < 1)
            velocity_ = sf::Vector2f(ORC_SPEED, ORC_SPEED);
        currPos_ += dt.asSeconds() * velocity_;
    } else {
        p_->TakeDamage(2);
        std::cout << "oof!" << std::endl;
    }
    //when a monster dies it disappears and gives the player score
    if (hp_ <= 0) {
        active_ = false;
        p_->AddScore(5 * (1 + p_->GetDifficulty()));
    }
}


//subclass orge, chases the player at constantly increasing speed
Orge::Orge(float x, float y, Player* p)
    : Monster(x, y, sf::Vector2f(0, 0), ORGE_HP, p), aggro_(1)
{
    sprite_ = sf::Sprite(p->GetTexture(), sf::IntRect(101,181,22,28));
    sprite_.setScale(sf::Vector2f(2, 2));
    AdjustSpawn();
}

//determines the behavior of an Orge
void Orge::update(sf::Time dt) {
    if (p_->CanDie() && sprite_.getGlobalBounds().intersects(p_->GetSprite().getGlobalBounds())) {
        p_->TakeDamage(5);
        std::cout << "OOF!" << std::endl;
    } else {
        sf::Vector2f target = p_->GetPosition();
        sf::Vector2f diff = target - currPos_;
        diff = diff/(float)sqrt(diff.x*diff.x + diff.y*diff.y);
        velocity_ = diff * ORGE_SPEED * aggro_;
        currPos_ += dt.asSeconds() * velocity_;
    }
    //aggro determines how fast the orge chases the player, increases over time
    aggro_ += dt.asSeconds() * 0.25;
    //when a monster dies it disappears and gives the player score
    if (hp_ <= 0) {
        active_ = false;
        p_->AddScore(20 * (1 + p_->GetDifficulty()));
    }
}

//subclass Boss, the boss of the game. Defeat it for something interesting.

Boss::Boss(float x, float y, Player* p)
    : Monster(x, y, sf::Vector2f(0, 0), BOSS_HP, p), cooldown_(1.5) , waypoint_(sf::Vector2f(-1,-1))
{
    sprite_ = sf::Sprite(p->GetTexture(), sf::IntRect(160,177,33,31));
    sprite_.setScale(sf::Vector2f(2, 2));
    AdjustSpawn();
    SetHP((p->GetDifficulty()+1) * BOSS_HP);
    clock_.restart();
}

//Boss moves in a circle around the center of the room. Charges towards the player if its hp gets low.
void Boss::update(sf::Time dt) {
    if (p_->CanDie() && sprite_.getGlobalBounds().intersects(p_->GetSprite().getGlobalBounds())) {
        p_->TakeDamage(8);
        std::cout << "BIG OOF!" << std::endl;
        if (!(hp_ > BOSS_HP*BOSS_RAGE_LIMIT)) cooldown_ = BOSS_COOLDOWN;
    }
    if (hp_ > BOSS_HP*BOSS_RAGE_LIMIT) { // normal boss
        auto bounds = sprite_.getGlobalBounds();
        sf::Vector2f center = p_->GetRoom()->GetSize()*(float)0.5-sf::Vector2f(bounds.width/6,bounds.height/6);
        sf::Vector2f accdir = currPos_ - center;
        float radius = std::sqrt(accdir.x*accdir.x + accdir.y*accdir.y);
        float elapsed = clock_.getElapsedTime().asSeconds();
        currPos_ = center + sf::Vector2f(std::cos(BOSS_SPEED/radius*elapsed), std::sin(BOSS_SPEED/radius*elapsed))*radius;
        int proj_dmg = 5;
        float projectilespeed = 200;
        if(cooldown_ == 0 &&volley_ > 0){
            //calculate the direction of the projectile with the linear combination of boss and player location vectors. 
            sf::Vector2f projectile_direction = p_->GetPosition() + p_->GetVelocity() *( dt.asSeconds() * 100) - currPos_;
            //calculate speed with the pythagoran theorem
            float vlength = std::sqrt(projectile_direction.x*projectile_direction.x + projectile_direction.y * projectile_direction.y);
            //velocity = unit direction vector * speed
            sf::Vector2f projectile_velocity(projectile_direction.x/vlength*projectilespeed,
                                            projectile_direction.y/vlength*projectilespeed);
            //create new projectile, the creation point is the middle of the boss instead of the top-left corner, the coefficient is 6 because graphics are scaled 3 times from the actual game logic.
            p_->GetRoom()->AddProjectile(std::move(std::make_unique<Projectile>(
                sf::Vector2f(currPos_.x + (sprite_.getGlobalBounds().width/6),
                currPos_.y+ sprite_.getGlobalBounds().height/6),
                projectile_velocity, proj_dmg, true, p_->GetTexture())));
            volley_--;
            if(volley_ == 0) {
                cooldown_ = BOSS_COOLDOWN * ((float)hp_/10);
                std::cout << "cooldown is: " << cooldown_ << std::endl;
            }
        }
        else{
            cooldown_ -= std::min(cooldown_, dt.asSeconds());
            if(cooldown_ == 0) { volley_ = 10; }
        }


    } else { // enraged boss
        sf::Vector2f v0(velocity_);
        if(std::min(std::abs(waypoint_.x - currPos_.x),std::abs(waypoint_.y - currPos_.y)) < 0.1 ) { 
            waypoint_ = sf::Vector2f(-1,-1);
            cooldown_ = 1;
        }
        if(waypoint_ == sf::Vector2f(-1,-1)){
            waypoint_ = p_->GetPosition();
        }
        
        sf::Vector2f diff = waypoint_ - currPos_;
        diff = diff/(float)sqrt(diff.x*diff.x + diff.y*diff.y);
        if (cooldown_ == 0) { // charge towards player
            velocity_ = diff * (BOSS_SPEED* 4);
        }
        else {
            cooldown_ -= std::min(dt.asSeconds(), cooldown_);
            if (velocity_.y < 0) velocity_.y += BOSS_DECCEL * dt.asSeconds();
            if (velocity_.x < 0) velocity_.x += BOSS_DECCEL * dt.asSeconds();
            if (velocity_.y > 0) velocity_.y -= BOSS_DECCEL * dt.asSeconds();
            if (velocity_.x > 0) velocity_.x -= BOSS_DECCEL * dt.asSeconds();
        }
        currPos_ += 0.5f * dt.asSeconds() * (velocity_ + v0);
    }
    if (hp_ <= 0) {
        active_ = false;
        p_->AddScore(100 * (1 + p_->GetDifficulty()));
    }
    if(currPos_.x < 0) { currPos_.x = 0; velocity_.x = 0; }
    if(currPos_.y < 0) { currPos_.y = 0; velocity_.y = 0; }
    auto bounds = sprite_.getGlobalBounds();
    if (currPos_.x+bounds.width/3 > p_->GetRoom()->GetWidth()) {
        currPos_ = sf::Vector2f(p_->GetRoom()->GetWidth()-bounds.width/3, currPos_.y);
        velocity_.x = 0;
    }
    if (currPos_.y+bounds.height/3 > p_->GetRoom()->GetHeight()) {
        currPos_ = sf::Vector2f(currPos_.x, p_->GetRoom()->GetHeight()-bounds.height/3);
        velocity_.y = 0;
    }
}
