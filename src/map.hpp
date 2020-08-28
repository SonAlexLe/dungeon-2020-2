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

    ~Map() = default;

    std::shared_ptr<Room> GetStartingRoom();


private:

// Helper functions to break down constructing a map
    void map_init();

    std::shared_ptr<Room> room_init();

    int difficulty_;

    std::list<std::shared_ptr<Room>> rooms_;

    std::shared_ptr<Player> p_;


};
