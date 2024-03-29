cmake_minimum_required(VERSION 3.21)
project(rtype)

# check if compiler supports c++23
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++23" COMPILER_SUPPORTS_CXX23)

if (COMPILER_SUPPORTS_CXX23)
    set(CMAKE_CXX_STANDARD 23)
else()
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fdiagnostics-color=always")
endif()
if (WIN32)
    add_definitions(-DNOMINMAX)
endif()

# Set the project to be built in the 'build' directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

add_subdirectory(deps)

message(STATUS "CMake toolchain: ${CMAKE_TOOLCHAIN_FILE}")
include(${CMAKE_TOOLCHAIN_FILE})

if (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
else()
    find_package(OpenAL CONFIG REQUIRED)
endif()

find_package(spdlog CONFIG REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(Lua REQUIRED)      # adding the CONFIG here doesnt work for some reason
find_package(sol2 CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# Add subdirectories for the engine and client
add_subdirectory(editor)
add_subdirectory(runtime)
add_subdirectory(client)
add_subdirectory(server)

include(cmake/Package.cmake)