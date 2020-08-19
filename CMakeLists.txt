cmake_minimum_required(VERSION 3.1.0)
project(dungeons)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCES src/main.cpp src/game.cpp src/entity.cpp src/player.cpp src/map.cpp src/room.cpp src/projectile.hpp src/monster.cpp src/orc.cpp)

# Detect and add SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(dungeons ${SOURCES})

target_link_libraries (dungeons sfml-graphics sfml-window sfml-system)