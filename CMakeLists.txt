cmake_minimum_required(VERSION 3.20)
project(Telemetry)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB sources src/main.cpp)
file(GLOB headers src/PacketDefs.h Constants.h)

add_executable(main ${sources} ${headers})
