#include "room.hpp"


Room::Room() : size_(300, 300), player_(nullptr), item_(nullptr), Nconn_(nullptr), Sconn_(nullptr), Wconn_(nullptr), Econn_(nullptr) {

}

Room::~Room() {}

std::shared_ptr<Player> Room::GetPlayer() { return player_; }

void Room::RemovePlayer() { player_ = nullptr; }

void Room::AddPlayer(std::shared_ptr<Player> p) { player_ = p; }

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

sf::Vector2f Room::GetSize() {return size_;}
double Room::GetWidth() { return size_.x; }
double Room::GetHeight() { return size_.y; }

void Room::SetNConn(std::shared_ptr<Room> r) { Nconn_ = r; }
void Room::SetSConn(std::shared_ptr<Room> r) { Sconn_ = r; }
void Room::SetWConn(std::shared_ptr<Room> r) { Wconn_ = r; }
void Room::SetEConn(std::shared_ptr<Room> r) { Econn_ = r; }