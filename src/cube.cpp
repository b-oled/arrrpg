// arrrpg - cube.cpp
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

#include "cube.h"
#include <memory.h>

//--------------------------------------------------------------------------------------------------

namespace arrrpg {

//--------------------------------------------------------------------------------------------------

Cube::Cube()
{
    //setup shader
    shader.LoadFromFile(GL_VERTEX_SHADER, "shader/simple_vertex.glsl");
    shader.LoadFromFile(GL_FRAGMENT_SHADER, "shader/simple_fragment.glsl");
    shader.CreateAndLinkProgram();
    shader.Use();
        shader.AddAttribute("vVertex");
        shader.AddUniform("MVP");
        shader.AddUniform("time");
    shader.UnUse();

    init();
}

//--------------------------------------------------------------------------------------------------

Cube::~Cube()
{
    destroy();
}

//--------------------------------------------------------------------------------------------------

int
Cube::total_vertices()
{
    return 8; // 4 vertices, for each front/back face
}

//--------------------------------------------------------------------------------------------------

int
Cube::total_indices()
{
    return 36; // 6 indices per side, 6 sides
}

//--------------------------------------------------------------------------------------------------

GLenum
Cube::primitive_type()
{
    return GL_TRIANGLES;
}

//--------------------------------------------------------------------------------------------------

void
Cube::fill_vertex_buffer(GLfloat *pBuffer)
{
    GLfloat cube_vertices[] = {
        // front
        -0.1, -0.1,  0.1,
         0.1, -0.1,  0.1,
         0.1,  0.1,  0.1,
        -0.1,  0.1,  0.1,
        // back
        -0.1, -0.1, -0.1,
         0.1, -0.1, -0.1,
         0.1,  0.1, -0.1,
        -0.1,  0.1, -0.1,
      };
    memcpy(pBuffer, cube_vertices, sizeof(cube_vertices));
}

//--------------------------------------------------------------------------------------------------

void
Cube::fill_index_buffer(GLshort *pBuffer)
{
    GLushort cube_elements[] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // top
        3, 2, 6,
        6, 7, 3,
        // back
        7, 6, 5,
        5, 4, 7,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // left
        4, 0, 3,
        3, 7, 4,
        // right
        1, 5, 6,
        6, 2, 1,
      };
    memcpy(pBuffer, cube_elements, sizeof(cube_elements));
}

//--------------------------------------------------------------------------------------------------

void
Cube::SetCustomUniforms()
{
}

//--------------------------------------------------------------------------------------------------

} // namespace arrrpg
