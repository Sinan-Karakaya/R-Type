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
