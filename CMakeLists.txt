cmake_minimum_required(VERSION 2.8.9)
project(dungeons)

add_subdirectory(../build)

set(SOURCES src/main.cpp)

# Detect and add SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(build/DDDdungeons ${SOURCES})

target_link_libraries (Dongon sfml-graphics sfml-window sfml-system)