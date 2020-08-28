#pragma once

#include "room.hpp"
#include "connection.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <monster.hpp>

//Map object represents a floor of the dungeon
class Map
{
public:

    Map() {}

    Map(int difficulty, std::shared_ptr<Player> p);

    ~Map() {}

    std::shared_ptr<Room> GetStartingRoom();


private:

// Helper functions to break down constructing a map
    void map_init();

    std::shared_ptr<Room> room_init();

    int difficulty_;

    std::list<std::shared_ptr<Room>> rooms_;

    std::shared_ptr<Player> p_;


};
