#include "room.hpp"


Room::Room() : size_(100,100) {}

std::list<Entity*> Room::GetPlayer() { return player_; }

void Room::AddPlayer(Entity* p) { player_.push_back(p); }

std::list<Entity*> Room::GetEnemies() { return enemies_; }

void Room::AddEnemy(Entity* e) { enemies_.push_back(e); }

std::list<Connection*> Room::GetConnections() {return connections_; }

void Room::AddConnection(Connection* c) { connections_.push_back(c); }

std::list<Entity*> Room::GetProjectiles() { return projectiles_; }

void Room::AddProjectile(Entity* p) { projectiles_.push_back(p); }

std::list<Obstacle*> Room::GetObstacles() { return obstacles_; }

void Room::AddObstacle(Obstacle* r) { obstacles_.push_back(r); }

double Room::GetWidth() { return size_.x; }

double Room::GetHeight() { return size_.y; }
