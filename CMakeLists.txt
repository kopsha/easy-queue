cmake_minimum_required(VERSION 2.6.0)

project(easy-app C)
add_subdirectory(lib)
add_executable(easy-app main.c)

target_include_directories(easy-app PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/lib")
target_link_libraries(easy-app PUBLIC easy-queue-lib)
