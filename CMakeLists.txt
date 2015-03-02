cmake_minimum_required(VERSION 2.8.5)

project(arrrpg)

add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

SET(sources
src/main.cpp
src/runtime.cpp
src/runtime.h
src/world.cpp
src/world.h
src/node.cpp
src/node.h
src/shader.cpp
src/shader.h
src/stdinc.h
shader/simple_fragment.glsl
shader/simple_vertex.glsl
)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(arrrpg glfw GLEW GL)

add_custom_command(TARGET arrrpg PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:arrrpg>/shader)
