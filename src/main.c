// arrrpg - main.c
// Copyright (C) 2015 Ole Diederich <ole@schwarzekiste.info>
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

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    GLFWwindow* window;
} arpgState;

static arpgState state;
static arpgState* st = &state;

int
main (int argc, char** argv) {

    // no arg handling atm
    (void) argc;
    (void) argv;

    // gl setup
    if (!glewInit()) {
        fprintf(stderr, "Failed to initialize GLEW!\n");
        return 1;
    }
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW!\n");
        return 1;
    }

    // window setup
    st->window = glfwCreateWindow(640, 480, "Arrrpg v0.0", NULL, NULL);
    if (!st->window) {
        printf( "Couldn't create window!\n" );
        return 1;
    }

    glfwMakeContextCurrent(st->window);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // render loop
    while (1)
    {
        glFlush();

        glfwSwapBuffers(st->window);
        glfwPollEvents();

        if (glfwWindowShouldClose(st->window)) {
            break;
        }
    }

    // teardown
    glfwTerminate();

    return 0;
}
