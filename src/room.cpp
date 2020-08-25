#include "room.hpp"


Room::Room() : size_(300,300) {}

void Room::AddEnemy(Monster* e) {
    enemies_.push_back(e);
}

std::list<Monster*> Room::GetEnemies() {
    return enemies_;
}

void Room::RemovePlayer() { player_ = nullptr; }

void Room::AddPlayer(Player* p) { player_ = p; }

std::list<Monster*> Room::GetEnemies() { return enemies_; }

void Room::AddEnemy(Monster* e) { enemies_.push_back(e); }

void Room::RemoveEnemy(Monster* m) {
    for (auto it = enemies_.begin(); it != enemies_.end(); it++) {
        if (*it == m) { enemies_.erase(it); break; }
    }
}

sf::Vector2f Room::GetSize() {
    return size_;
}

void Room::AddProjectile(Projectile *pew){
    projectiles_.push_back(pew);
}

void Room::SetEConn(Room* r) { Econn_ = r; }
