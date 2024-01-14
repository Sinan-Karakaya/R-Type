cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE CLIENT_SOURCES src/*.cpp src/*.hpp src/*.h)
add_executable(client ${CLIENT_SOURCES})

add_definitions(-DWIN32_LEAN_AND_MEAN)

target_include_directories(client PRIVATE src include ${CMAKE_SOURCE_DIR}/common ${CMAKE_SOURCE_DIR}/runtime/src)

target_link_libraries(client PRIVATE ImGui-SFML::ImGui-SFML)
target_link_libraries(client PRIVATE sfml-graphics sfml-window sfml-system sfml-network)
target_link_libraries(client PRIVATE spdlog::spdlog)
target_link_libraries(client PRIVATE runtime)

if (NOT APPLE)
    target_link_libraries(client PRIVATE runtime sfml-audio)
    add_custom_command(TARGET client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-audio>
        $<TARGET_FILE_DIR:client>
    )
endif()

set_target_properties(client PROPERTIES
    OUTPUT_NAME "rtype_client"
)

add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
    $<TARGET_FILE:sfml-graphics>
    $<TARGET_FILE:sfml-window>
    $<TARGET_FILE:sfml-network>
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

add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:client>
    ${CMAKE_BINARY_DIR}
)
