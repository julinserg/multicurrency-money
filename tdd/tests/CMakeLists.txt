# CMake version string
cmake_minimum_required(VERSION 3.0)

# Project
project(test_money)

# Executable
add_executable(${PROJECT_NAME} "")

# Sources
file(GLOB SOURCES "*.h" "*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})

# Includes
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)

# Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE gtest gmock)

# Tests
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})


