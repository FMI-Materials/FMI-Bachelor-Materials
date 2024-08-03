cmake_minimum_required(VERSION 3.15)
project(Tema2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tema2 main.cpp include/nfa.h src/nfa.cpp include/dfa.h src/dfa.cpp src/reggram.cpp include/reggram.h include/state.h include/regex.h src/regex.cpp)