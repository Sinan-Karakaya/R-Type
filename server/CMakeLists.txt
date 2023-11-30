cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE SERVER_SOURCES src/*.cpp src/*.hpp src/*.h)
add_executable(server ${SERVER_SOURCES})

target_include_directories(server PRIVATE src include)

target_link_libraries(server PRIVATE asio::asio)
target_link_libraries(server PRIVATE runtime)

add_dependencies(server runtime)

if (DEFINED BUILD_TESTS)
    list(REMOVE_ITEM SERVER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp")
    add_subdirectory(tests)
endif()