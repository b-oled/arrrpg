cmake_minimum_required(VERSION 2.8.5)

project(arrrpg)

add_definitions(-std=c99 -O0)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

add_executable( ${PROJECT_NAME}
src/main.c
src/camera.h
src/camera.c
src/helper.c
src/helper.h
src/matrix.c
src/matrix.h
shader/simple_vertex.glsl
shader/simple_fragment.glsl
)

add_subdirectory(external/kazmath)

target_link_libraries(arrrpg glfw GLEW GL kazmath)

add_custom_command(TARGET arrrpg PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:arrrpg>/shader)
