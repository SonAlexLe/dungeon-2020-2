cmake_minimum_required(VERSION 3.1.0)
project(dungeons)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCES src/main.cpp src/game.cpp src/entity.cpp src/player.cpp src/map.cpp src/room.cpp)

# Detect and add SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(dungeons ${SOURCES})

target_link_libraries (dungeons sfml-graphics sfml-window sfml-system)