cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE EDITOR_SOURCES src/*.cpp src/*.hpp src/*.h)

if (WIN32)
    add_executable(editor WIN32 ${EDITOR_SOURCES})
else()
    add_executable(editor ${EDITOR_SOURCES})
endif()

if (APPLE)
    target_link_libraries(editor PRIVATE ${COCOA_LIBRARY})
else()
    target_link_libraries(editor PRIVATE sfml-audio)
endif()

target_link_libraries(editor PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(editor PRIVATE ImGui-SFML::ImGui-SFML)
target_link_libraries(editor PRIVATE spdlog::spdlog)
target_link_libraries(editor PRIVATE unofficial::nativefiledialog::nfd)
target_include_directories(editor PRIVATE
    src
    include
    ${SFML_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}
    ${NFD_INCLUDE_DIR}
    ${nlohmann_json_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/common
)

if (NOT APPLE)
    add_custom_command(TARGET editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-audio>
        $<TARGET_FILE_DIR:editor>
    )
endif()

add_custom_command(TARGET editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:sfml-window>
    $<TARGET_FILE:sfml-graphics>
    $<TARGET_FILE:sfml-system>
    $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
    $<TARGET_FILE:spdlog::spdlog>
    $<TARGET_FILE:unofficial::nativefiledialog::nfd>
    $<TARGET_FILE:runtime>
    $<TARGET_FILE_DIR:editor>
)

add_custom_command(TARGET editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/editor/assets
    $<TARGET_FILE_DIR:editor>/assets
)
