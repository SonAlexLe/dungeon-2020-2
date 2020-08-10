#pragma once
#include "room.hpp"


//Map is a group of rooms that are connected by "Connection"-entities.

//One considered implementation is to initialize rooms as an empty forest and use prim's algorithm (https://en.wikipedia.org/wiki/Prim%27s_algorithm) and random weightings to connect the rooms.

//Another simpler implementation would be to initialize a 2D grid as an array, have the starting room be in the middle of the grid, then create a room on one of its neighbors and 
// recursively repeat on that neighbor and its neighbors until the desired amount of rooms have been placed.
 


//player object should have reference to the room it is in as a variable.
//rooms should be adressable individually

class Map
{
public:

    /*The amount of rooms initialized will be based on the difficult or depth of the dungeon. This will be passed to the map constructor by the game loop.
     How the generator should rougly works:
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
    Room* GetStartingRoom();


private:
    int difficulty_;

    std::list<Room*> rooms_;

    std::list<Entity*> connections_;

};