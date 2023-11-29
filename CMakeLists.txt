cmake_minimum_required(VERSION 3.21)
project(rtype)

set(CMAKE_CXX_STANDARD 20)
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

if (DEFINED PACKAGE AND CMAKE_BUILD_TYPE STREQUAL "Release")

include(InstallRequiredSystemLibraries)
cpack_add_component_group(client
    REQUIRED
    DISPLAY_NAME "Runtime"
    DESCRIPTION "The runtime of the game"
    INSTALL_TYPES Full
)
endif()
