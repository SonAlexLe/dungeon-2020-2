cmake_minimum_required(VERSION 2.8.9)
project(dungeons)

set(SOURCES main.cpp entity.cpp game.cpp graphics.cpp map.cpp player.cpp room.cpp)

# Detect and add SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(DDDdungeons ${SOURCES})

target_link_libraries (DDDdungeons sfml-graphics sfml-window sfml-system)