#include "room.hpp"


Room::Room() : player_(nullptr), item_(nullptr), Nconn_(nullptr), Sconn_(nullptr), Wconn_(nullptr), Econn_(nullptr) {
    std::pair<double,double> size(100, 100);
    size_ = size;
}

Room::~Room() {
    for (Connection* c : connections_) {
        delete c;
    }
    for (Monster* m : enemies_) {
        delete m;
    }
}

Player* Room::GetPlayer() { return player_; }

void Room::RemovePlayer() { player_ = nullptr; }

void Room::AddPlayer(Player* p) { player_ = p; }

std::list<Monster*> Room::GetEnemies() { return enemies_; }

void Room::AddEnemy(Monster* e) { enemies_.push_back(e); }

void Room::RemoveEnemy(Monster* m) {
    for (auto it = enemies_.begin(); it != enemies_.end(); it++) {
        if (*it == m) { enemies_.erase(it); break; }
    }
}

void Room::AddItem(Item* i) { item_ = i; }

std::list<Connection*> Room::GetConnections() {return connections_; }

void Room::AddConnection(Connection* c) { connections_.push_back(c); }

// std::list<Entity*> Room::GetProjectiles() { return projectiles_; }

// void Room::AddProjectile(Entity* p) { projectiles_.push_back(p); }

// std::list<Obstacle*> Room::GetObstacles() { return obstacles_; }

// void Room::AddObstacle(Obstacle* r) { obstacles_.push_back(r); }

double Room::GetWidth() { return size_.first; }

double Room::GetHeight() { return size_.second; }

void Room::SetNConn(Room* r) { Nconn_ = r; }

void Room::SetSConn(Room* r) { Sconn_ = r; }

void Room::SetWConn(Room* r) { Wconn_ = r; }

void Room::SetEConn(Room* r) { Econn_ = r; }