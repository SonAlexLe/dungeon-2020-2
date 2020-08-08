#include "room.hpp"


Room::Room() : size_(100,100) {}

std::list<Entity*> Room::GetPlayer() {
    return player_;
}

std::list<Entity*> Room::GetEnemies() {
    return enemies_;
}

std::list<Entity*> Room::GetConnections() {
    return connections_;
}

std::list<Entity*> Room::GetProjectiles() {
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