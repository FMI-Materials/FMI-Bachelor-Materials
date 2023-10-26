cmake_minimum_required(VERSION 3.17.1)
project(ChessAi)

set(CMAKE_CXX_STANDARD 20)

add_executable(Checkmate
        main.cpp
        include/brain.h include/draw.h include/materials.h include/piece.h include/pieces.h include/rules.h include/table.h include/utils.h
        src/brain.cpp src/draw.cpp src/materials.cpp src/piece.cpp src/pieces.cpp src/rules.cpp src/table.cpp
        include/exception.h)

# Linking SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
target_link_libraries(Checkmate sfml-graphics sfml-window sfml-system sfml-audio)

