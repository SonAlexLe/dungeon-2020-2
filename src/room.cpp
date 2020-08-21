#include "room.hpp"


Room::Room(){
    std::pair<double,double> size(100, 100);
    size_ = size;
}

Player* Room::GetPlayer() { return player_; }

void Room::AddPlayer(Player* p) { player_ = p; }

std::list<Monster*> Room::GetEnemies() { return enemies_; }

void Room::AddEnemy(Monster* e) { enemies_.push_back(e); }

void Room::RemoveEnemy(Monster* m) {
    for (auto it = enemies_.begin(); it != enemies_.end(); it++) {
        if (*it == m) { enemies_.erase(it); break; }
    }
}

std::list<Connection*> Room::GetConnections() {return connections_; }

void Room::AddConnection(Connection* c) { connections_.push_back(c); }

// std::list<Entity*> Room::GetProjectiles() { return projectiles_; }

// void Room::AddProjectile(Entity* p) { projectiles_.push_back(p); }

// std::list<Obstacle*> Room::GetObstacles() { return obstacles_; }

// void Room::AddObstacle(Obstacle* r) { obstacles_.push_back(r); }

double Room::GetWidth() { return size_.first; }

double Room::GetHeight() { return size_.second; }
