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

#include "runtime.h"
#include "world.h"

#include "stdinc.h"
#include <unistd.h>
#include <GLFW/glfw3.h>

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
        /* Create a windowed mode window and its OpenGL context */
        m_window = glfwCreateWindow(640, 480, "Arrrpg v0.0", NULL, NULL);

        if (!m_window)
        {
            glfwTerminate();
        }
    }

    // init world
    m_world = new World();

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
    glfwMakeContextCurrent(m_window);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    while (!glfwWindowShouldClose(m_window))
    {
        m_world->draw( );
        glFlush();
        glfwSwapBuffers(m_window);

        glfwPollEvents();
     }

}

//--------------------------------------------------------------------------------------------------

} // namespace arrrpg
