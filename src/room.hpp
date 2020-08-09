#pragma once
#include <list>
#include <utility>
#include "projectile.hpp"

class Entity;

class Room {
public:
    // For simplicity sake all rooms will be squares of the same size so all rooms are default constructed
    Room();
    // Destructor needs to handle emptying all containers
    ~Room() {}

    // Each room has containers for each type of entity contained in it and interfaces for accessing each container
    // Since all these objects share a base class you could just have one container for all of them but travesing this container would be very tedious.

    std::list<Entity*> GetPlayer();
    std::list<Entity*> GetEnemies();
    // Connection entities are doors/trapdoors/etc that connect to other rooms or floors
    std::list<Entity*> GetConnections();
    std::list<Projectile*> GetProjectiles();
    // Obstacles can be unpassable map geometry. Hazards(lava/spikes) could also be in obstacles or could be considered enemies without movement
    std::list<Entity*> GetObstacles();

    double GetWidth();
    double GetHeight();
    sf::Vector2f GetSize();

    void AddProjectile(Projectile *);

protected:

    // Types for containers need to be updated once different types of entities are implemented

    sf::Vector2f size_;
    std::list<Entity*> player_;
    std::list<Entity*> enemies_;
    std::list<Entity*> connections_;
    std::list<Projectile*> projectiles_;
    std::list<Entity*> obstacles_;

    int width_;
    
    int height_;

};
