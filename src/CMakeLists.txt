cmake_minimum_required(VERSION 2.8.9)
project(dungeons)

include_directories(include)

set(SOURCES main.cpp entity.cpp game.cpp graphics.cpp item.cpp map.cpp player.cpp)

add_executable(DDDdungeons ${SOURCES})
