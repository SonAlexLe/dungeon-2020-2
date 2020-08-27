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
class Connection;
class Monster;

class Room {
public:
    //constructs a new square room
    Room();

    // Destructor needs to handle emptying all containers
    ~Room();

    // Each room has containers for each type of entity contained in it and interfaces for accessing each container
    // Since all these objects share a base class you could just have one container for all of them but travesing this container would be very tedious.

    /* Player* GetPlayer();

    void AddPlayer(Player* p);

    void RemovePlayer(); */

    std::list<std::shared_ptr<Monster>>& GetEnemies();
    void AddEnemy(std::shared_ptr<Monster>);

    // Connection entities are doors/trapdoors/etc that connect to other rooms or floors
    std::list<std::shared_ptr<Connection>>& GetConnections();
    void AddConnection(std::shared_ptr<Connection>);

    void AddItem(std::shared_ptr<Item>);
    
    std::list<std::shared_ptr<Projectile>>& GetProjectiles();
    void CheckProjectiles();

    void AddProjectile(std::shared_ptr<Projectile>);

    void RemoveProjectile(std::shared_ptr<Projectile>);

    bool IsClear();

    std::string GetType();

    void SetType(std::string t);

    // Obstacles can be unpassable map geometry. Hazards(lava/spikes) could also be in obstacles or could be considered enemies without movement
    // std::list<Obstacle*> GetObstacles();

    // void AddObstacle(Obstacle*);

    double GetWidth();
    double GetHeight();
    sf::Vector2f GetSize();

    void SetNConn(std::shared_ptr<Room> r);

    std::shared_ptr<Room> GetNConn();

    void SetSConn(std::shared_ptr<Room> r);

    std::shared_ptr<Room> GetSConn();

    void SetWConn(std::shared_ptr<Room> r);

    std::shared_ptr<Room> GetWConn();

    void SetEConn(std::shared_ptr<Room> r);

    std::shared_ptr<Room> GetEConn();


protected:

    // Types for containers need to be updated once different types of entities are implemented

    sf::Vector2f size_;

    //Player* player_;

    std::list<std::shared_ptr<Monster>> enemies_;

    std::list<std::shared_ptr<Connection>> connections_;

    std::shared_ptr<Item> item_;

    std::string type_;

    std::list<std::shared_ptr<Projectile>> projectiles_;

    //Rooms neighbors
    std::shared_ptr<Room> Nconn_;

    std::shared_ptr<Room> Sconn_;

    std::shared_ptr<Room> Wconn_;

    std::shared_ptr<Room> Econn_;

};