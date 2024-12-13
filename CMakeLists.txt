
cmake_minimum_required(VERSION 3.0)


project(BattleShip)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(BattleShip
    board.cpp
    game.cpp
    player.cpp
    ship.cpp
    source.cpp
    utility.cpp
)


target_include_directories(BattleShip PRIVATE .)
