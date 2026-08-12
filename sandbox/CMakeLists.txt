cmake_minimum_required(VERSION 3.31)
project(sandbox)

set(CMAKE_C_FLAGS "-Wall -Wextra")

file(GLOB_RECURSE SRC_FILES src/*.c)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE engine)
target_include_directories(${PROJECT_NAME} PRIVATE include)
