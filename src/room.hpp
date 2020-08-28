#pragma once
#include "entity.hpp"
#include "connection.hpp"
#include <SFML/System.hpp>
#include "monster.hpp"
#include "item.hpp"
#include "projectile.hpp"
#include <list>
#include <utility>

class Entity;
class Connection;
class Monster;

/*Each room can have within it monsters, projectiles, connections and items.
Besides these containers a room has pointers to its neighboring rooms and type-tag to tell if the room is special
For interacting with these containers rooms have multiple setters and getters as interfaces
*/
class Room {
public:
    Room();

    ~Room();

    std::list<std::shared_ptr<Monster>>& GetEnemies();

    void AddEnemy(std::shared_ptr<Monster>);

    std::list<std::shared_ptr<Connection>>& GetConnections();

    void AddConnection(std::shared_ptr<Connection>);

    void AddItem(std::shared_ptr<Item>);

    std::list<std::shared_ptr<Item>>& GetItems();
    
    std::list<std::shared_ptr<Projectile>>& GetProjectiles();

    void CheckProjectiles();

    void AddProjectile(std::shared_ptr<Projectile>);

    void RemoveProjectile(std::shared_ptr<Projectile>);

    //A room is considered cleared when all monsters in it are inactive
    bool IsClear();

    //Determines if the room is special
    std::string GetType();

    void SetType(std::string t);

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


    sf::Vector2f size_;

    std::list<std::shared_ptr<Monster>> enemies_;

    std::list<std::shared_ptr<Connection>> connections_;

    std::list<std::shared_ptr<Item>> items_;

    std::string type_;

    std::list<std::shared_ptr<Projectile>> projectiles_;

    //Rooms neighbors in each cardinal direction
    std::shared_ptr<Room> Nconn_;

    std::shared_ptr<Room> Sconn_;

    std::shared_ptr<Room> Wconn_;

    std::shared_ptr<Room> Econn_;

};