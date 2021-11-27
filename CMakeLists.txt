cmake_minimum_required(VERSION 3.10)

project(easy-app)

set(CMAKE_C_FLAGS_PROFILE --coverage)
set(CMAKE_CXX_FLAGS_PROFILE --coverage)
set(CMAKE_CXX_STANDARD 11)

set(ZQ_SOURCE include/easy_queue.h)
add_executable(example-app main.c ${ZQ_SOURCE})

target_include_directories(example-app PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(example-app -fprofile-arcs)

# google test stuff
find_package(GTest CONFIG REQUIRED)
enable_testing()
include(GoogleTest)
add_executable(tests main_tests.cpp ${ZQ_SOURCE})
target_include_directories(tests PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_definitions(-fprofile-arcs -ftest-coverage)
target_link_libraries(tests GTest::gtest -fprofile-arcs)
