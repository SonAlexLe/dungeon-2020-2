#include "room.hpp"


Room::Room() : size_(300, 300), item_(nullptr), Nconn_(nullptr), Sconn_(nullptr), Wconn_(nullptr), Econn_(nullptr) {

}

Room::~Room() {}

/* Player* Room::GetPlayer() { return player_; }

void Room::RemovePlayer() { player_ = nullptr; }

void Room::AddPlayer(Player* p) { player_ = p; } */

std::list<std::shared_ptr<Monster>>& Room::GetEnemies() {
    return enemies_;
}

void Room::AddEnemy(std::shared_ptr<Monster> e) { enemies_.push_back(e); }

void Room::AddProjectile(std::shared_ptr<Projectile> pew){
    projectiles_.push_back(pew);
}

void Room::AddItem(std::shared_ptr<Item> i) { item_ = i; }

std::list<std::shared_ptr<Connection>>& Room::GetConnections() {return connections_; }
void Room::AddConnection(std::shared_ptr<Connection> c) { connections_.push_back(c); }

std::list<std::shared_ptr<Projectile>>& Room::GetProjectiles() { return projectiles_; }

bool Room::IsClear() {
    for (auto m : enemies_) {
        if( m->isActive()) {return false;}
    }
    return true;
}

// std::list<Obstacle*> Room::GetObstacles() { return obstacles_; }

// void Room::AddObstacle(Obstacle* r) { obstacles_.push_back(r); }

sf::Vector2f Room::GetSize() {return size_;}
double Room::GetWidth() { return size_.x; }
double Room::GetHeight() { return size_.y; }

void Room::SetNConn(std::shared_ptr<Room> r) { Nconn_ = r; }

std::shared_ptr<Room> Room::GetNConn() { return Nconn_; }

void Room::SetSConn(std::shared_ptr<Room> r) { Sconn_ = r; }

std::shared_ptr<Room> Room::GetSConn() { return Sconn_; }

void Room::SetWConn(std::shared_ptr<Room> r) { Wconn_ = r; }

std::shared_ptr<Room> Room::GetWConn() { return Wconn_; }

void Room::SetEConn(std::shared_ptr<Room> r) { Econn_ = r; }

std::shared_ptr<Room> Room::GetEConn() { return Econn_; }
