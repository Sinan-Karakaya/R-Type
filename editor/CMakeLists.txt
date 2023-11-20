cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE EDITOR_SOURCES src/*.cpp src/*.hpp src/*.h)
add_executable(editor ${EDITOR_SOURCES})
target_include_directories(editor PRIVATE src)

# Fetch and add imgui-sfml as a dependency
target_link_libraries(editor PRIVATE ImGui-SFML::ImGui-SFML sfml-graphics sfml-window sfml-system)
target_link_libraries(editor PRIVATE spdlog::spdlog)
target_link_libraries(editor PRIVATE nfd)
target_include_directories(editor PRIVATE
    src
    ${SFML_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}
    ${NFD_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    include
)

add_custom_command(TARGET editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
    $<TARGET_FILE:sfml-graphics>
    $<TARGET_FILE:sfml-window>
    $<TARGET_FILE:sfml-system>
    $<TARGET_FILE:spdlog::spdlog>
    $<TARGET_FILE:nfd>
    $<TARGET_FILE:runtime>
    $<TARGET_FILE_DIR:editor>
)

add_custom_command(TARGET editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/editor/assets
    $<TARGET_FILE_DIR:editor>/assets
)