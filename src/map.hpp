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

    Map(int difficulty, Player* p);

    ~Map() {}

    Room* GetStartingRoom();


private:

// Helper functions to break down constructing a map
    void map_init();

    std::unique_ptr<Room> room_init();

    int difficulty_;

    std::list<std::unique_ptr<Room>> rooms_;

    Player* p_;


};
