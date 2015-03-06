// arrrpg - runtime.cpp
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

#include "stdinc.h"
#include "runtime.h"
#include "world.h"
#include "cube.h"
#include "shader.h"

#include <iostream>
#include <unistd.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//--------------------------------------------------------------------------------------------------

namespace arrrpg {

#define INITIAL_WIDTH 1700
#define INITIAL_HEIGHT 900

//--------------------------------------------------------------------------------------------------

Runtime::Runtime()
    :
    m_window( NULL ),
    m_world( NULL ),
    m_P(glm::mat4(1)),
    m_width(INITIAL_WIDTH),
    m_height(INITIAL_HEIGHT),
    m_camx(0.0f),
    m_camy(0.0f),
    m_camrZ(0.0f),
    m_camdist(-10.0f)
{
    // init GL

    if (glfwInit())
    {
        // window params
        glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        /* Create a windowed mode window and its OpenGL context */
        m_window = glfwCreateWindow(INITIAL_WIDTH, INITIAL_HEIGHT, "Arrrpg v0.0", NULL, NULL);
        ARRRPG_CHECK_GL_ERROR;

        glfwSetWindowUserPointer(m_window, this);
        glfwSetFramebufferSizeCallback(m_window, glfw_fb_size_callback);
        glfwSetKeyCallback(m_window, glfw_key_callback);

        glfwMakeContextCurrent(m_window);

        // init GLEW
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            std::cerr<<"Error: "<< glewGetErrorString(err) << std::endl;
        }
        else
        {
            if (GLEW_VERSION_3_3)
            {
                std::cout<<"Driver supports OpenGL 3.3\nDetails:" << std::endl;
            }
        }

        std::cout << "\tUsing glew " << glewGetString(GLEW_VERSION) << std::endl;
        std::cout << "\tVendor: " << glGetString (GL_VENDOR) << std::endl;
        std::cout << "\tRenderer: " << glGetString (GL_RENDERER) << std::endl;
        std::cout << "\tVersion: " << glGetString (GL_VERSION) << std::endl;
        std::cout << "\tGLSL:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        //setup cam
        glViewport (0, 0, (GLsizei) INITIAL_WIDTH, (GLsizei) INITIAL_HEIGHT);
        m_P = glm::perspective(45.0f, (GLfloat)INITIAL_WIDTH/INITIAL_HEIGHT, 1.f, 1000.f);

    }
}

//--------------------------------------------------------------------------------------------------

Runtime::~Runtime()
{
    if (m_world)
        delete m_world;
    if (m_cube)
        delete m_cube;
    glfwTerminate();
}

//--------------------------------------------------------------------------------------------------

void
Runtime::start()
{
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // init world
//    m_world = ARRRPG_NEW( World(50, 50) );
//    m_world->init();

    m_cube = ARRRPG_NEW( Cube(500, 500) );
    m_cube->init();
    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        float rX=25, rY=-40;

        glm::mat4 T	  = glm::translate(glm::mat4(1.0f), glm::vec3(m_camx, m_camy, m_camdist));
        glm::mat4 Rx  = glm::rotate(T,  rX, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 MV  = glm::rotate(Rx, rY, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 MVP = m_P * MV;

//        float time = (glfwGetTime()*25+0.5f);
//        m_world->time(time);
//        m_world->render(glm::value_ptr(MVP));
        m_cube->render(glm::value_ptr(MVP));
        glfwSwapBuffers(m_window);

        glfwPollEvents();
     }

}

//--------------------------------------------------------------------------------------------------

void
Runtime::on_viewport_resize(int w, int h)
{
    m_width = w;
    m_height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    m_P = glm::perspective(45.0f, (GLfloat)w/h, 1.f, 1000.f);
}

//--------------------------------------------------------------------------------------------------

void
Runtime::on_key_callback(int key, int scancode, int action, int mods)
{
    ARRRPG_UNUSED(scancode);
    ARRRPG_UNUSED(mods);
    if ( key == GLFW_KEY_W ) {
        m_camdist+=0.1;
    } else if ( key == GLFW_KEY_A ) {
        m_camx++;
    } else if ( key == GLFW_KEY_S ) {
        m_camdist-=0.1;
    } else if ( key == GLFW_KEY_D ) {
        m_camx--;
    } else if ( key == GLFW_KEY_Q ) {
        m_camrZ-=0.01;
    } else if ( key == GLFW_KEY_E ) {
        m_camrZ+=0.01;
    } else if ( key == GLFW_KEY_X ) {
        m_camy--;
    } else if ( key == GLFW_KEY_Z ) {
        m_camy++;
}
}

//--------------------------------------------------------------------------------------------------

} // namespace arrrpg
