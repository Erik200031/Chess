cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

project(Chess)

add_executable(
    Chess
    main.cpp 
    game/chess.cpp 
    board/board.cpp 
    board/chess_board.cpp
)