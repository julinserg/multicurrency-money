cmake_minimum_required(VERSION 3.5)

project(tdd LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tdd main.cpp)

add_subdirectory(tests)

set(gtest_force_shared_crt ON)
add_subdirectory(googletest)

