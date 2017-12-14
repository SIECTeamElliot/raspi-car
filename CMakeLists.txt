cmake_minimum_required(VERSION 2.6)

# Project configuration
project(CarPark)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
add_definitions( "-std=c++11" )

set(EXECUTABLE_OUTPUT_PATH "bin")
include_directories(${PROJECT_SRC_DIR}/include)
file(GLOB SOURCES src/Can.cpp src/communicationSTM.cpp)


add_executable(exec src/main.cpp ${SOURCES})
target_link_libraries(exec pthread)