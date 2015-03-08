cmake_minimum_required(VERSION 2.8.5)

project(arrrpg)

add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

add_executable(${PROJECT_NAME}
src/main.cpp
src/Camera.cpp
src/Camera.h
src/Entity.cpp
src/Entity.h
src/FreeCamera.cpp
src/FreeCamera.h
src/Runtime.cpp
src/Runtime.h
src/World.cpp
src/World.h
src/Cube.cpp
src/Cube.h
src/Shader.cpp
src/Shader.h
src/stdinc.h
shader/simple_fragment.glsl
shader/simple_vertex.glsl
README.md
)

target_link_libraries(arrrpg glfw GLEW GL)

add_custom_command(TARGET arrrpg PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:arrrpg>/shader)
