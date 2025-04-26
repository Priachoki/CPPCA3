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

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.6.2/lib/cmake/SFML)  # your installed SFML directory
find_package(SFML COMPONENTS system window graphics network REQUIRED)

include_directories(C:/SFML-2.6.2/include)
target_link_libraries(CPPCA3 sfml-system sfml-window sfml-graphics)
