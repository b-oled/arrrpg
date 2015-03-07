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
#include "freecamera.h"
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
    m_width(INITIAL_WIDTH),
    m_height(INITIAL_HEIGHT),
    m_fov(45.0f)
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
        glfwSetCursorPosCallback(m_window, glfw_mousepos_callback);
        glfwSetMouseButtonCallback(m_window, glfw_mousebtn_callback);

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
        std::cout << "\tVendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "\tRenderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "\tVersion: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "\tGLSL:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        glViewport (0, 0, (GLsizei) INITIAL_WIDTH, (GLsizei) INITIAL_HEIGHT);
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

    //setup camera
    m_camera.reset( ARRRPG_NEW( FreeCamera() ) );
    m_camera->position(glm::vec3(5));
    glm::vec3 p = glm::vec3(5);
    glm::vec3 look = glm::normalize(p);

    //rotate the camera for proper orientation
    float yaw = glm::degrees(float(atan2(look.z, look.x) + M_PI));
    float pitch = glm::degrees(asin(look.y));
    m_rX = yaw;
    m_rY = pitch;
    m_camera->rotate(m_rX, m_rY, 0);
    m_camera->setup_projection(m_fov, (GLfloat)INITIAL_WIDTH/INITIAL_HEIGHT);

    m_cube.reset( ARRRPG_NEW( Cube(800, 800) ) );
    m_cube->init();
    while (!glfwWindowShouldClose(m_window))
    {
        m_last_time = m_current_time;
        m_current_time = glfwGetTime();
        m_dt = m_current_time-m_last_time;

        m_camera->update();

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //set the camera transformation
        glm::mat4 MV	= m_camera->view_matrix();
        glm::mat4 P     = m_camera->projection_matrix();
        glm::mat4 MVP	= P*MV;

        m_cube->time(m_current_time);
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
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    m_camera->setup_projection(m_fov, w/h);
}

//--------------------------------------------------------------------------------------------------

void
Runtime::on_key_callback(int key, int scancode, int action, int mods)
{
    ARRRPG_UNUSED(scancode);
    ARRRPG_UNUSED(mods);
    ARRRPG_UNUSED(action);

    if ( key == GLFW_KEY_W )
    {
        m_camera->walk((m_dt+1));
    }
    else if ( key == GLFW_KEY_A )
    {
        m_camera->strafe(-(m_dt+1));
    }
    else if ( key == GLFW_KEY_S )
    {
        m_camera->walk(-(m_dt+1));
    }
    else if ( key == GLFW_KEY_D )
    {
        m_camera->strafe((m_dt+1));
    }
    else if ( key == GLFW_KEY_Q )
    {
        m_camera->lift((m_dt+1));
    }
    else if ( key == GLFW_KEY_Z )
    {
        m_camera->lift(-(m_dt+1));
    }

}

//--------------------------------------------------------------------------------------------------

void
Runtime::on_cursorpos_callback(double x, double y)
{
    if (!m_mouse_look) {
        //m_fov += (y - m_mouse_oldy) / 100.0f;
        //m_camera->setup_projection(m_fov, m_camera->get_aspect_ratio());
    } else {
        m_rY += (y - m_mouse_oldy) / 100.0f;
        m_rX += (m_mouse_oldx - x) / 100.0f;
//        if(useFiltering)
//            filterMouseMoves(rX, rY);
//        else {
//            mouseX = rX;
//            mouseY = rY;
//        }
        m_camera->rotate(m_rX,m_rY, 0);
    }
    m_mouse_oldx = x;
    m_mouse_oldy = y;
}

//--------------------------------------------------------------------------------------------------

void
Runtime::on_mousebtn_callback(int btn, int action, int mods)
{
    ARRRPG_UNUSED( action );
    ARRRPG_UNUSED( mods );

    if (btn == GLFW_MOUSE_BUTTON_1)
        m_mouse_look = !m_mouse_look;
}

//--------------------------------------------------------------------------------------------------

} // namespace arrrpg
