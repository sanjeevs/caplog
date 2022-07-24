cmake_minimum_required(VERSION 3.10)
project(Test)

add_subdirectory(logger)

add_executable(test_simple test_simple.cpp)
target_link_libraries(test_simple PUBLIC logger)
target_include_directories(test_simple PUBLIC "${PROJECT_SOURCE_DIR}/logger")

add_executable(test_threads test_threads.cpp)
target_link_libraries(test_threads PUBLIC logger)
target_link_libraries(test_threads PRIVATE pthread)
target_include_directories(test_threads PUBLIC "${PROJECT_SOURCE_DIR}/logger")


find_package(CapnProto CONFIG REQUIRED)
capnp_generate_cpp(audiologSources audiologHeaders audiolog.capnp)
add_executable(test_audiomsg test_audiomsg.cpp ${audiologSources})
target_link_libraries(test_audiomsg PRIVATE logger CapnProto::capnp)
target_include_directories(test_audiomsg PRIVATE "${PROJECT_SOURCE_DIR}/logger" "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(print_audiomsg print_audiomsg.cpp ${audiologSources})
target_link_libraries(print_audiomsg PRIVATE CapnProto::capnp)
target_include_directories(print_audiomsg PRIVATE ${CMAKE_CURRENT_BINARY_DIR})