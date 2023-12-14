cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE RUNTIME_SOURCES src/*.cpp src/*.hpp src/*.h)
add_library(runtime SHARED ${RUNTIME_SOURCES})
target_include_directories(runtime PRIVATE src)

# Fetch and add imgui-sfml as a dependency
target_link_libraries(runtime PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(runtime PRIVATE spdlog::spdlog OpenAL::OpenAL)
target_link_libraries(runtime PRIVATE ${LUA_LIBRARIES} sol2)
target_include_directories(runtime PRIVATE src ${CMAKE_SOURCE_DIR}/common)
target_include_directories(runtime PRIVATE
    ${nlohmann_json_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIR}
    ${LUA_INCLUDE_DIR}
)

# TODO: TEST SOL2 TO REMOVE FOR MAIN BRANCH
# Find sol2 package
find_package(sol2 CONFIG REQUIRED)

# add a simple executable for testing
add_executable(test_app main.cpp)

# cpoyt test.lua file to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test.lua ${CMAKE_CURRENT_BINARY_DIR}/test.lua COPYONLY)

target_link_libraries(test_app PRIVATE runtime sfml-graphics sfml-window sfml-system)

target_include_directories(test_app PRIVATE ${CMAKE_SOURCE_DIR}/src)  
target_include_directories(test_app PRIVATE ${SFML_INCLUDE_DIR} ${LUA_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/common)
target_include_directories(test_app PRIVATE ${sol2_INCLUDE_DIRS})

target_compile_definitions(test_app PRIVATE ${sol2_DEFINITIONS})
target_link_libraries(test_app PRIVATE ${sol2_LIBRARIES})

