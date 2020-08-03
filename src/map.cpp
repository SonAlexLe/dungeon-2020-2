//map generation
//todo: version of generateMap() which returns a single square room

#pragma once
#include "map.hpp"

Map::Map(int difficulty) : difficulty_(difficulty) {

    //Initialize starting room
    rooms_.push_back(new Room);
}

Room Map::GetStartingRoom() {
    return rooms_.front();
}