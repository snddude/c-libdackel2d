cmake_minimum_required(VERSION 3.31)
project(engine)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_C_FLAGS "-Wall -Wextra")

set(SDL_X11 OFF)
set(SDL_STATIC ON)
set(SDL_SHARED OFF)
set(SDL_TEST_LIBRARY OFF)
set(SDL_VENDOR_INFO Dackel2D)

set(SDLIMAGE_VENDORED ON)
set(SDLIMAGE_STRICT ON)
set(SDLIMAGE_XV OFF)
set(SDLIMAGE_ANI OFF)
set(SDLIMAGE_LBM OFF)
set(SDLIMAGE_PCX OFF)
set(SDLIMAGE_PNM OFF)
set(SDLIMAGE_QOI OFF)
set(SDLIMAGE_TIF OFF)
set(SDLIMAGE_XCF OFF)
set(SDLIMAGE_XPM OFF)
set(SDLIMAGE_AVIF OFF)
set(SDLIMAGE_BACKEND_STB OFF)

set(SDLTTF_VENDORED ON)
set(SDLTTF_STRICT ON)

add_subdirectory(vendor/stb_ds)
add_subdirectory(vendor/SDL)
add_subdirectory(vendor/SDL_image)
add_subdirectory(vendor/SDL_ttf)

file(GLOB_RECURSE SRC_FILES src/*.c)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC m)      # math.h
target_link_libraries(${PROJECT_NAME} PUBLIC stb_ds) # Typesafe containers by Sean Barrett
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3_image::SDL3_image)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3_ttf::SDL3_ttf)
