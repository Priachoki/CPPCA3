cmake_minimum_required(VERSION 3.30)
project(CPPCA3)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPPCA3 main.cpp
        Crawler.cpp
        Crawler.h
        Board.cpp
        Board.h
        Bug.h
        Bug.cpp
        Hopper.h
        Hopper.cpp
        SpiralBug.h
        SpiralBug.cpp
)
