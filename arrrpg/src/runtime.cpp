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
#include "stdinc.h"
#include <unistd.h>
#include <GLFW/glfw3.h>

//---------------------------------------------------------------------------------------------------------------------

namespace arrrpg {

//---------------------------------------------------------------------------------------------------------------------

Runtime::Runtime()
    :
    m_window( NULL )
{
    /* Initialize the library */
    if (glfwInit())
    {
        /* Create a windowed mode window and its OpenGL context */
        m_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

        if (!m_window)
        {
            glfwTerminate();
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------

Runtime::~Runtime()
{
    glfwTerminate();
}

//---------------------------------------------------------------------------------------------------------------------

void
Runtime::start()
{
    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    // /* Loop until the user closes the window */
     while (!glfwWindowShouldClose(m_window))
     {


       glFlush();
       glfwSwapBuffers(m_window);

    //     /* Poll for and process events */
         glfwPollEvents();
     }    /* Make the window's context current */

}

//---------------------------------------------------------------------------------------------------------------------

} // namespace arrrpg
