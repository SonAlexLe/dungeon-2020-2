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
*/
class Room {
public:
    Room();

    ~Room();

    std::list<std::unique_ptr<Monster>>& GetEnemies();

    void AddEnemy(std::unique_ptr<Monster>);

    std::list<std::shared_ptr<Connection>>& GetConnections();

    void AddConnection(std::shared_ptr<Connection>);

    void AddItem(std::shared_ptr<Item>);

    std::list<std::shared_ptr<Item>>& GetItems();
    
    std::list<std::unique_ptr<Projectile>>& GetProjectiles();

    void CheckProjectiles();

    void AddProjectile(std::unique_ptr<Projectile>);

    void RemoveProjectile(std::unique_ptr<Projectile>);

    //A room is considered cleared when all monsters in it are inactive
    bool IsClear();

    std::string GetType();

    void SetType(std::string t);

    double GetWidth();

    double GetHeight();

    sf::Vector2f GetSize();

    void SetNConn(Room* r);

    Room* GetNConn();

    void SetSConn(Room* r);

    Room* GetSConn();

    void SetWConn(Room* r);

    Room* GetWConn();

    void SetEConn(Room* r);

    Room* GetEConn();


protected:


    sf::Vector2f size_;

    std::list<std::unique_ptr<Monster>> enemies_;

    std::list<std::shared_ptr<Connection>> connections_;

    std::list<std::shared_ptr<Item>> items_;

    std::string type_;

    std::list<std::unique_ptr<Projectile>> projectiles_;

    //Rooms neighbors
    Room* Nconn_;

    Room* Sconn_;

    Room* Wconn_;

    Room* Econn_;

};