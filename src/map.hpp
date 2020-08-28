#pragma once

#include "room.hpp"
#include "connection.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <monster.hpp>

//Map is a group of rooms that are connected by "Connection"-entities.

class Map
{
public:

    Map() {}

    Map(int difficulty, std::shared_ptr<Player> p);

    ~Map() {}

    Room* GetStartingRoom();


private:

// Helper functions to break down constructing a map
    void map_init();

    std::unique_ptr<Room> room_init();

    int difficulty_;

    std::list<std::unique_ptr<Room>> rooms_;

    std::shared_ptr<Player> p_;


};
