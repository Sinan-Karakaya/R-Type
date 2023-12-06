cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE NETWORK_SOURCES src/*.cpp src/*.hpp src/*.h)
add_library(network STATIC ${NETWORK_SOURCES})
target_include_directories(network PRIVATE src)

# Fetch and add imgui-sfml as a dependency
target_link_libraries(network PRIVATE asio::asio)
target_link_libraries(network PRIVATE spdlog::spdlog)

# WTF MAN, WE NEED TO FIND A BETTER WAY TO DO THIS
target_link_libraries(network PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(network PRIVATE ImGui-SFML::ImGui-SFML)
target_include_directories(network PRIVATE ${SFML_INCLUDE_DIR} ${IMGUI_INCLUDE_DIR})

target_include_directories(network PRIVATE src ${CMAKE_SOURCE_DIR}/common)
