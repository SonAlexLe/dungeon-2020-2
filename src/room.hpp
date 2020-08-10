#pragma once
#include "entity.hpp"
#include <list>
#include <utility>

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
    
    std::list<Entity*> GetProjectiles();

    // Obstacles can be unpassable map geometry. Hazards(lava/spikes) could also be in obstacles or could be considered enemies without movement
    std::list<Entity*> GetObstacles();

    double GetWidth();

    double GetHeight();

protected:

    // Types for containers need to be updated once different types of entities are implemented

    std::pair<double, double> size_;

    std::list<Entity*> player_;

    std::list<Entity*> enemies_;

    std::list<Entity*> connections_;

    std::list<Entity*> projectiles_;

    std::list<Entity*> obstacles_;

    int width_;
    
    int height_;

};
