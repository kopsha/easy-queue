cmake_minimum_required(VERSION 3.10)

project(easy-app)

set(CMAKE_CXX_STANDARD 11)

add_executable(example-app main.c include/easy_queue.h)

target_include_directories(example-app PUBLIC "${PROJECT_SOURCE_DIR}/lib")
target_link_libraries(example-app PUBLIC easy-queue-lib)

# google test stuff
find_package(GTest CONFIG REQUIRED)
enable_testing()
include(GoogleTest)
add_executable(tests main_tests.cpp include/easy_queue.h)
target_include_directories(tests PUBLIC "${PROJECT_SOURCE_DIR}/lib")
target_link_libraries(tests GTest::gtest)
target_link_libraries(tests easy-queue-lib)
