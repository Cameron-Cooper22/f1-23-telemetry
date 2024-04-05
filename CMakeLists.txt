cmake_minimum_required(VERSION 3.27)
project(Telemetry)

set(CMAKE_CXX_STANDARD 20)

add_executable(Telemetry src/main.cpp)
target_link_libraries(Telemetry ws2_32)
