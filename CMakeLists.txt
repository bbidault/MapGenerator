cmake_minimum_required(VERSION 2.8)

project( MapGenerator )

set (CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )

add_executable( MapGenerator 
                include/world_map.h 
                include/pixel.h
                include/common.h
                src/main.cpp 
                src/world_map.cpp
                src/common.cpp )

target_link_libraries( MapGenerator 
                       ${OpenCV_LIBS} )

target_include_directories( MapGenerator 
                            PRIVATE 
                            include
                            src )
