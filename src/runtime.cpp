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
#include "shader.h"

#include <iostream>
#include <unistd.h>

//--------------------------------------------------------------------------------------------------

namespace arrrpg {

//--------------------------------------------------------------------------------------------------

Runtime::Runtime()
    :
    m_window( NULL ),
    m_world( NULL )
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
        m_window = glfwCreateWindow(1280, 720, "Arrrpg v0.0", NULL, NULL);

        if (!m_window)
        {
            glfwTerminate();
        }
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

        // init world
        m_world = ARRRPG_NEW( Renderable< World >);
        m_world->init();
    }
}

//--------------------------------------------------------------------------------------------------

Runtime::~Runtime()
{
    glfwTerminate();
}

//--------------------------------------------------------------------------------------------------

void
Runtime::start()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    while (!glfwWindowShouldClose(m_window))
    {

        usleep(100000);
        glFlush();
        glfwSwapBuffers(m_window);

        glfwPollEvents();
     }

}

//--------------------------------------------------------------------------------------------------

} // namespace arrrpg
