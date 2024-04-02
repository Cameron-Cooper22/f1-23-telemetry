cmake_minimum_required(VERSION 3.20)
project(Telemetry)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file()

add_executable(connection src/connect.cpp)
