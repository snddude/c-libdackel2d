cmake_minimum_required(VERSION 3.31)
project(engine)

add_subdirectory(vendor/SDL)
add_subdirectory(vendor/SDL_image)
add_subdirectory(vendor/SDL_ttf)

file(GLOB_RECURSE SRC_FILES src/*.c)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3_image::SDL3_image)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3_ttf::SDL3_ttf)
