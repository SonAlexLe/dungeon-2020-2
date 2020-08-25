#include "room.hpp"


Room::Room() : size_(sf::Vector2f(100.0, 100.0)), player_(nullptr), item_(nullptr), Nconn_(nullptr), Sconn_(nullptr), Wconn_(nullptr), Econn_(nullptr) {}

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

std::list<Monster*>& Room::GetEnemies() { return enemies_; }

void Room::AddEnemy(Monster* e) { enemies_.push_back(e); }

void Room::RemoveEnemy(Monster* m) {
    for (auto it = enemies_.begin(); it != enemies_.end(); it++) {
        if (*it == m) { enemies_.erase(it); break; }
    }
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

void Room::AddItem(Item* i) { item_ = i; }

std::list<Connection*>& Room::GetConnections() {return connections_; }

void Room::AddConnection(Connection* c) { connections_.push_back(c); }

std::list<Projectile*>& Room::GetProjectiles() { return projectiles_; }

// std::list<Obstacle*> Room::GetObstacles() { return obstacles_; }

// void Room::AddObstacle(Obstacle* r) { obstacles_.push_back(r); }

double Room::GetWidth() { return size_.x; }

double Room::GetHeight() { return size_.y; }

void Room::SetNConn(Room* r) { Nconn_ = r; }

void Room::SetSConn(Room* r) { Sconn_ = r; }

void Room::SetWConn(Room* r) { Wconn_ = r; }

void Room::SetEConn(Room* r) { Econn_ = r; }