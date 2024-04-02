cmake_minimum_required(VERSION 3.20)
project(Telemetry)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(connection src/connect.cpp)

file(GLOB sources src/*.cpp)
file(GLOB headers src/*.h)

list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/connect.cpp)
add_executable(main ${sources} ${headers})
