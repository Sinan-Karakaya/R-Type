cmake_minimum_required(VERSION 3.21)

add_definitions(-DASIO_STANDALONE)

file(GLOB_RECURSE server_SOURCES src/*.cpp src/*.hpp src/*.h)
add_executable(server ${server_SOURCES})

target_include_directories(server PRIVATE ${CMAKE_SOURCE_DIR}/deps/submodules/asio/include)
target_include_directories(server PRIVATE src include ${CMAKE_SOURCE_DIR}/common)
target_link_libraries(server PRIVATE spdlog::spdlog)
target_link_libraries(server PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(server PRIVATE ImGui-SFML::ImGui-SFML sfml-graphics sfml-window sfml-system)

target_link_libraries(server PRIVATE Boost::asio)
if (WIN32)
    target_link_libraries(server PRIVATE ws2_32 wsock32)
endif()

add_custom_command(TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
    $<TARGET_FILE:sfml-graphics>
    $<TARGET_FILE:sfml-window>
    $<TARGET_FILE:sfml-system>
    $<TARGET_FILE:spdlog::spdlog>
    $<TARGET_FILE:runtime>
    $<TARGET_FILE_DIR:server>
)