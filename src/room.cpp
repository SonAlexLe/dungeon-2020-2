#include "room.hpp"


Room::Room() : size_(300,300) {}

void Room::AddEnemy(Monster* e) {
    enemies_.push_back(e);
}

std::list<Monster*> Room::GetEnemies() {
    return enemies_;
}

std::list<Entity*> Room::GetConnections() {
    return connections_;
}

std::list<Projectile*> Room::GetProjectiles() {
    return projectiles_;
}

std::list<Entity*> Room::GetObstacles() {
    return obstacles_;
}

double Room::GetWidth() {
    return size_.x;
}

double Room::GetHeight() {
    return size_.y;
}

sf::Vector2f Room::GetSize() {
    return size_;
}

void Room::AddProjectile(Projectile *pew){
    projectiles_.push_back(pew);
}
