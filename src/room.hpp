#pragma once
#include "entity.hpp"
#include "connection.hpp"
#include <SFML/System.hpp>
#include "monster.hpp"
#include "item.hpp"
// #include "obstacle.hpp"
#include "projectile.hpp"
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

    Player* GetPlayer();

    void AddPlayer(Player* p);

    void RemovePlayer();

    std::list<Monster*>& GetEnemies();

    void AddEnemy(Monster*);

    void RemoveEnemy(Monster*);

    // Connection entities are doors/trapdoors/etc that connect to other rooms or floors
    std::list<Connection*>& GetConnections();

    void AddConnection(Connection*);

    void AddItem(Item*);
    
    std::list<Projectile*>& GetProjectiles();

    void AddProjectile(Projectile*);

    void RemoveProjectile(Projectile*);

    // Obstacles can be unpassable map geometry. Hazards(lava/spikes) could also be in obstacles or could be considered enemies without movement
    // std::list<Obstacle*> GetObstacles();

    // void AddObstacle(Obstacle*);

    double GetWidth();

    double GetHeight();

    sf::Vector2f GetSize();

    void SetNConn(Room* r);

    void SetSConn(Room* r);

    void SetWConn(Room* r);

    void SetEConn(Room* r);


protected:

    // Types for containers need to be updated once different types of entities are implemented

    sf::Vector2f size_;

    Player* player_;

    std::list<Monster*> enemies_;

    std::list<Connection*> connections_;

    Item* item_;

    std::list<Projectile*> projectiles_;

    // std::list<Obstacle*> obstacles_;

    //Rooms neighbors
    Room* Nconn_;

    Room* Sconn_;

    Room* Wconn_;

    Room* Econn_;

};
