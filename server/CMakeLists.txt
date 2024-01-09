cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE SERVER_SOURCES src/*.cpp src/*.hpp src/*.h)
add_executable(server ${SERVER_SOURCES})

add_definitions(-DWIN32_LEAN_AND_MEAN)

target_include_directories(server PRIVATE src include ${CMAKE_SOURCE_DIR}/common ${CMAKE_SOURCE_DIR}/runtime/src)
target_include_directories(server PRIVATE
    ${SFML_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}
    ${nlohmann_json_SOURCE_DIR}/include
)

find_package(Threads REQUIRED)

if (NOT APPLE)
    target_link_libraries(server PRIVATE sfml-audio)
endif()

target_link_libraries(server PRIVATE sfml-graphics sfml-window sfml-system sfml-network)
target_link_libraries(server PRIVATE ImGui-SFML::ImGui-SFML)
target_link_libraries(server PRIVATE asio::asio)
target_link_libraries(server PRIVATE spdlog::spdlog)
target_link_libraries(server PRIVATE runtime)
target_link_libraries(server PRIVATE Threads::Threads)

set_target_properties(server PROPERTIES
    OUTPUT_NAME "rtype_server"
)

add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
    $<TARGET_FILE:spdlog::spdlog>
    $<TARGET_FILE:runtime>
    $<TARGET_FILE_DIR:server>
)

add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:server>
    ${CMAKE_BINARY_DIR}
)

if (DEFINED BUILD_TESTS)
    list(REMOVE_ITEM SERVER_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
    add_subdirectory(tests)
endif()
