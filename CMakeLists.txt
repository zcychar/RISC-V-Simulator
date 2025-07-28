cmake_minimum_required(VERSION 3.15)

project(risc-v-simulate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

include_directories(include)

file(GLOB sources RELATIVE ${PROJECT_SOURCE_DIR} src/*.cpp)

add_executable(code ${sources})


