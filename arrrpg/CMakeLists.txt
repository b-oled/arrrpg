project(arrrpg)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_CXX_FLAGS "-std=c++0x")

aux_source_directory(src/ SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(arrrpg glfw GLU GL)

