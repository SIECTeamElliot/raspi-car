cmake_minimum_required(VERSION 2.6)

# Project configuration
project(CarPark)
set(EXECUTABLE_OUTPUT_PATH "bin")
include_directories(${PROJECT_SRC_DIR}/include)
file(GLOB SOURCES src/*.cpp src/*.c)


add_executable(exec src/main.cpp ${SOURCES})
target_link_libraries(exec pthread)