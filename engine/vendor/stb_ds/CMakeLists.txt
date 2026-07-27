cmake_minimum_required(VERSION 3.31)
project(stb_ds)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_sources(${PROJECT_NAME} PRIVATE src/stb_ds.c)
