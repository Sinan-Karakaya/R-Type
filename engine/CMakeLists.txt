cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE ENGINE_SOURCES src/*.cpp src/*.hpp src/*.h)
add_library(engine STATIC ${ENGINE_SOURCES})
target_include_directories(engine PRIVATE src)

# Fetch and add imgui-sfml as a dependency
target_link_libraries(engine PRIVATE ImGui-SFML::ImGui-SFML sfml-graphics sfml-window sfml-system)
target_include_directories(engine PRIVATE ${SFML_INCLUDE_DIR} ${IMGUI_INCLUDE_DIR})
