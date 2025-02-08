#minimum CMake VERSION
cmake_minimum_required(VERSION 3.21)

#Project name
project(
    ComputePipeline
    LANGUAGES C CXX
    VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list( APPEND SRC
      main.cpp
)


add_executable(${PROJECT_NAME} ${SRC})
target_include_directories( ${PROJECT_NAME} PUBLIC ./inc)