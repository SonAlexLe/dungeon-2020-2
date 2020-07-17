#pragma once
#include "map.hpp"
#include "entity.hpp"


class Game{
public:
    int GetScore();
    int GetDifficulty();


private:
    int score_;
    int difficulty_;
    Map dungeon_;
    
    
}