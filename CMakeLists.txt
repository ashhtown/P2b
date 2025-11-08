cmake_minimum_required(VERSION 3.29)
project(P2b)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(P2b
        main.cpp
        pokeFile.cpp
        algo1.cpp
)