cmake_minimum_required(VERSION 2.8)

# Project configuration
project(CarPark)
add_definitions( "-std=c++11 " )
# add_definitions( "-DDEBUG=true " )
add_definitions( "-Wall" )

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(EXECUTABLE_OUTPUT_PATH bin)
include_directories(include)
file(GLOB SOURCES src/*.cpp)

add_executable(exec ${SOURCES})
target_link_libraries(exec pthread)
target_link_libraries( exec ${Boost_LIBRARIES} )