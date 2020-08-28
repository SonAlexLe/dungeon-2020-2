#include "room.hpp"


Room::Room() : size_(300, 300), type_("default"), Nconn_(nullptr), Sconn_(nullptr), Wconn_(nullptr), Econn_(nullptr) {}

Room::~Room() {};

std::list<std::unique_ptr<Monster>>& Room::GetEnemies() {
    return enemies_;
}

void Room::AddEnemy(std::unique_ptr<Monster> e) { enemies_.push_back(std::move(e)); }

void Room::AddProjectile(std::unique_ptr<Projectile> pew){ projectiles_.push_back(std::move(pew)); }

void Room::AddItem(std::shared_ptr<Item> i) { items_.push_back(i); }

std::list<std::shared_ptr<Item>>& Room::GetItems() { return items_; }

std::list<std::shared_ptr<Connection>>& Room::GetConnections() {return connections_; }

void Room::AddConnection(std::shared_ptr<Connection> c) { connections_.push_back(c); }

std::list<std::unique_ptr<Projectile>>& Room::GetProjectiles() { return projectiles_; }

bool Room::IsClear() {
    for (auto const& m : enemies_) {
        if(m->isActive()) {return false;}
    }
    return true;
}

std::string Room::GetType() { return type_; }

void Room::SetType(std::string t) { type_ = t; }

sf::Vector2f Room::GetSize() {return size_;}

double Room::GetWidth() { return size_.x; }

double Room::GetHeight() { return size_.y; }

void Room::SetNConn(Room* r) { Nconn_ = r; }

Room* Room::GetNConn() { return Nconn_; }

void Room::SetSConn(Room* r) { Sconn_ = r; }

Room* Room::GetSConn() { return Sconn_; }

void Room::SetWConn(Room* r) { Wconn_ = r; }

Room* Room::GetWConn() { return Wconn_; }

void Room::SetEConn(Room* r) { Econn_ = r; }

Room* Room::GetEConn() { return Econn_; }
