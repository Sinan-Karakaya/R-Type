cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE SERVER_TESTS_SOURCES src/*.cpp src/*.hpp src/*.h)
add_executable(server_test ${SERVER_TESTS_SOURCES} ${SERVER_SOURCES})

target_include_directories(server_test PRIVATE src ../include)

target_link_libraries(server_test PRIVATE asio::asio)
target_link_libraries(server_test PRIVATE runtime)
target_link_libraries(server_test PRIVATE Catch2::Catch2WithMain)
add_dependencies(server_test runtime)
