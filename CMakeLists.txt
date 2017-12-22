cmake_minimum_required(VERSION 2.8)

# Project configuration
project(CarPark)
add_definitions( "-std=c++11 " )
add_definitions( "-DDEBUG=true " )

set(EXECUTABLE_OUTPUT_PATH bin)
include_directories(include)
file(GLOB SOURCES src/*.cpp)

add_executable(exec ${SOURCES})
target_link_libraries(exec pthread)