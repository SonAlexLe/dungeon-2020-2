#pragma once

#include "room.hpp"
#include "connection.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <monster.hpp>

//Map is a group of rooms that are connected by "Connection"-entities.

//player object should have reference to the room it is in as a variable.
//rooms should be adressable individually

class Map
{
public:

    /*The amount of rooms initialized will be based on the difficult or depth of the dungeon. This will be passed to the map constructor by the game loop.
     How the generator should roughly works:
    - Generate a starting room and place the player there
    - Delete the previous map
    - Initialize empty rooms
    - Create connections
    - Fill rooms (One idea is to have text files for preconstructed room layouts that will be read randomly)
    - Add special rooms (boss, shop, item rooms, etc)
    */

    Map() {}

    Map(int difficulty);

    ~Map() {}

    // Should be the head of rooms_
    std::shared_ptr<Room> GetStartingRoom();


private:

// Helper functions to break down constructing a map
    void map_init();

    std::shared_ptr<Room> room_init();

    int difficulty_;

    std::list<std::shared_ptr<Room>> rooms_;

    // std::list<Connection*> connections_;

};
