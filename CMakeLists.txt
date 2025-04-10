cmake_minimum_required(VERSION 3.29)
project(bls2)

set(CMAKE_CXX_STANDARD 20)

add_executable(bls2 main.cpp
        src/Board.cpp
        src/Board.h
        src/Crawler.cpp
        src/Crawler.h
        src/utils/Direction.h
        src/utils/Position.h
        src/utils/Bug.h
        src/utils/Bug.cpp)
