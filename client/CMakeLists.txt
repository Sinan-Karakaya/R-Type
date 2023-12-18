cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE CLIENT_SOURCES src/*.cpp src/*.hpp src/*.h)
add_executable(client ${CLIENT_SOURCES})
target_link_libraries(client PRIVATE runtime ImGui-SFML::ImGui-SFML sfml-graphics sfml-window sfml-system spdlog::spdlog)
target_include_directories(client PRIVATE src ${CMAKE_SOURCE_DIR}/common)

if (NOT APPLE)
    target_link_libraries(client PRIVATE runtime sfml-audio)
    add_custom_command(TARGET client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-audio>
        $<TARGET_FILE_DIR:client>
    )
endif()

add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
    $<TARGET_FILE:sfml-graphics>
    $<TARGET_FILE:sfml-window>
    $<TARGET_FILE:sfml-system>
    $<TARGET_FILE:spdlog::spdlog>
    $<TARGET_FILE:runtime>
    $<TARGET_FILE_DIR:client>
)

add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/client/assets
    $<TARGET_FILE_DIR:client>/assets
)
