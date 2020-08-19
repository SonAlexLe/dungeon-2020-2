#include "entity.hpp"


/*Each connection object functions as a doorway to a different room or new map 
Connections inherit the Entity class, 
on top of that each connection has a reference to another connection and a method for traversing from one connection to the other.
By default connections are locked and need to be unlocked by key or by clearing the room (subject to change)
*/
class Connection : public Entity {
public:
    Connection();

    Connection(float x, float y);
    
    void unlock();

    const std::string GetSpriteName() const; 

    void update(sf::Time dt);

    void load();

    void connect(Room* r);

    /*WIP. Maybe should take the player as a parameter or is called when a connection and a player collide.
     Also needs to place the player on the correct spot after traversing. (Tried to connect connections together) */
    void traverse();

private:
    Room* connected_to_;

    bool locked_;
};