cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE RUNTIME_SOURCES src/*.cpp src/*.hpp src/*.h)
add_library(runtime SHARED ${RUNTIME_SOURCES})
target_include_directories(runtime PRIVATE src)

add_definitions(-DWIN32_LEAN_AND_MEAN)

if (NOT APPLE)
    target_link_libraries(runtime PRIVATE sfml-audio OpenAL::OpenAL)    
endif()

target_link_libraries(runtime PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(runtime PRIVATE spdlog::spdlog)
target_link_libraries(runtime PRIVATE asio::asio)
target_link_libraries(runtime PRIVATE ${LUA_LIBRARIES} sol2)
target_include_directories(runtime PRIVATE src ${CMAKE_SOURCE_DIR}/common)
target_include_directories(runtime PRIVATE
    ${nlohmann_json_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIR}
    ${LUA_INCLUDE_DIR}
)

add_custom_command(TARGET runtime POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:sfml-window>
    $<TARGET_FILE:sfml-audio>
    $<TARGET_FILE:sfml-graphics>
    $<TARGET_FILE:sfml-system>
    $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
    $<TARGET_FILE:spdlog::spdlog>
    $<TARGET_FILE:fmt::fmt>
    $<TARGET_FILE:OpenAL::OpenAL>
    $<TARGET_FILE:unofficial::nativefiledialog::nfd>
    $<TARGET_FILE:${LUA_LIBRARIES}>
    ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET runtime POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE_DIR:runtime>
    ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET runtime POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/r-type-game
    ${CMAKE_BINARY_DIR}/r-type-game
)

add_custom_command(TARGET runtime POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:editor>/assets
    ${CMAKE_BINARY_DIR}/assets
)
