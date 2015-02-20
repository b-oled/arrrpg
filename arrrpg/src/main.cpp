// arrrpg - main.cpp
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

#include <iostream>
#include <GLFW/glfw3.h>

using namespace std;

int
main( )
{
    // basic example from glfw.org
    GLFWwindow* window;

    if ( !glfwInit( ) )
        return -1;

    window = glfwCreateWindow( 640, 480, "arrrpg", NULL, NULL );
    if ( !window )
    {
        glfwTerminate( );
        return -1;
    }

    glfwMakeContextCurrent( window );

    while ( !glfwWindowShouldClose( window ) )
    {
        glfwSwapBuffers( window );
        glfwPollEvents( );
    }

    glfwTerminate( );

    return 0;
}

