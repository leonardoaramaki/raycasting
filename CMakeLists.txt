cmake_minimum_required(VERSION 3.15)
project(raycasting)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(raycasting
        main.cpp
        player.cpp
        player.h
        map.cpp
        map.h
        window.cpp
        window.h
        ray.cpp
        ray.h
        raycasting.h
        raycasting.cpp raycasting_data.h)

target_link_libraries(raycasting ${SDL2_LIBRARIES})
