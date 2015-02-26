cmake_minimum_required(VERSION 2.8)

project(arrrpg)

add_definitions(-std=c99 -O3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

aux_source_directory(src/ SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(arrrpg glfw GLEW GL)

