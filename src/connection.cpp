#include "connection.hpp"

Connection::Connection() : Entity() {}

Connection::Connection(float x, float y) : Entity(x, y) {}

void Connection::unlock() { locked_ = false;}

const std::string Connection::GetSpriteName() const {return "door.png";}

void Connection::update(sf::Time dt) {}

void Connection::load() {}

void Connection::connect(Room* r) { connected_to_ = r; }

void Connection::traverse() {}


