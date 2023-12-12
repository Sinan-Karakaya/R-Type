cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE NETWORK_SOURCES src/*.cpp src/*.hpp src/*.h)
add_library(network STATIC ${NETWORK_SOURCES})
target_include_directories(network PRIVATE src)

find_package(Threads REQUIRED)

target_link_libraries(network PRIVATE asio::asio)
target_link_libraries(network PRIVATE spdlog::spdlog)
target_link_libraries(network PRIVATE Threads::Threads)

target_include_directories(network PRIVATE src ${CMAKE_SOURCE_DIR}/common)
