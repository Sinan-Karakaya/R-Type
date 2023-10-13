cmake_minimum_required(VERSION 3.21)
project(rtype)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fdiagnostics-color=always")

# Set the project to be built in the 'build' directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps)

# Add subdirectories for the engine and client
add_subdirectory(engine)
add_subdirectory(client)