cmake_minimum_required(VERSION 2.8.5)

project(arrrpg)

add_definitions(-std=c99 -O3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

SET(sources
src/main.c
src/helper.c
src/helper.h
)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(arrrpg glfw GLEW GL)

