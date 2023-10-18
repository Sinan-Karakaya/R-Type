cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE CLIENT_SOURCES src/*.cpp src/*.hpp src/*.h)
add_executable(client ${CLIENT_SOURCES})
target_link_libraries(client PRIVATE engine)
target_include_directories(client PRIVATE src ${CMAKE_SOURCE_DIR}/include)

if(WIN32)
    if (BUILD_SHARED_LIBS)
        add_custom_command(TARGET client POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE:spdlog::spdlog>
            $<TARGET_FILE_DIR:client>
            )
    endif()
endif()