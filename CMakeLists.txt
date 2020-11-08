cmake_minimum_required(VERSION 3.1.0)
project(dungeons)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tutorial_compiler_flags INTERFACE)
target_compile_features(tutorial_compiler_flags INTERFACE cxx_std_17)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(tutorial_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-g;-Wall;-Wpedantic;-Wvla;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCES src/main.cpp src/game.cpp src/entity.cpp src/player.cpp src/map.cpp src/room.cpp src/projectile.hpp src/monster.cpp src/connection.cpp src/inventory.cpp src/inventoryItems.cpp src/item.cpp)

# Detect and add SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(dungeons ${SOURCES})

target_link_libraries (dungeons sfml-graphics sfml-window sfml-system sfml-audio)