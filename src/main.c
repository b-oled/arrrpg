// arrrpg - main.c
// Copyright (C) 2015 Ole Diederich <ole@rumgespinne.com>
// This file is part of arrrpg.
// arrrpg is free software; you can redistribute it and/or modify it
// under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation; either version 3 of the
// License, or (at your option) any later version.
//
// arrrpg is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#define _DEFAULT_SOURCE

#include "helper.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    GLuint position;
    GLuint program;
    GLuint matrix;
} Attribs;

typedef struct {
    GLFWwindow* window;
    int height;
    int width;
} ArpgState;

static ArpgState state;
static ArpgState* st = &state;

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

void
draw_triangles(Attribs* attribs, GLuint buffer_id) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glEnableVertexAttribArray(attribs->position);
    glVertexAttribPointer(
       attribs->position,  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int
main (int argc, char** argv) {

    // no arg handling atm
    (void) argc;
    (void) argv;

    // init glfw
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW!\n");
        return 1;
    }

    // window params
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // window / context setup
    st->window = glfwCreateWindow(1280, 760, "Arrrpg v0.0", NULL, NULL);
    if (!st->window) {
        printf( "Couldn't create window!\n" );
        return 1;
    }
    glfwMakeContextCurrent(st->window);

    // init GLEW
    glewExperimental = GL_TRUE; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW!\n");
        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // test
    GLuint triangle_buffer = make_buffer(sizeof(g_vertex_buffer_data), g_vertex_buffer_data);

    Attribs triangle = {0};

    GLuint program;
    program = create_program("shader/simple_vertex.glsl", "shader/simple_fragment.glsl");
    triangle.program = program;
    triangle.position = glGetAttribLocation(program, "position");
    triangle.matrix = glGetUniformLocation(program, "matrix");

    // render loop
    while (1)
    {
        glfwGetFramebufferSize(st->window, &st->width, &st->height);
        glViewport(0, 0, st->width, st->height);

        draw_triangles(&triangle, triangle_buffer);
        glfwSwapBuffers(st->window);
        glfwPollEvents();

        usleep(50 * 1000);

        if (glfwWindowShouldClose(st->window)) {
            break;
        }
    }

    // teardown
    glfwTerminate();

    return 0;
}
