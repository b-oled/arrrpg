cmake_minimum_required(VERSION 2.8.5)

project(arrrpg)

add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_executable(${PROJECT_NAME}
src/main.cpp
src/camera.cpp
src/camera.h
src/freecamera.cpp
src/freecamera.h
src/runtime.cpp
src/runtime.h
src/world.cpp
src/world.h
src/cube.cpp
src/cube.h
src/shader.cpp
src/shader.h
src/stdinc.h
src/renderable.h
shader/simple_fragment.glsl
shader/simple_vertex.glsl
)

target_link_libraries(arrrpg glfw GLEW GL)

add_custom_command(TARGET arrrpg PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:arrrpg>/shader)
