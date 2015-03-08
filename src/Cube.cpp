// arrrpg - Cube.cpp
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

#include "Cube.h"
#include <memory.h>

//--------------------------------------------------------------------------------------------------

namespace arrrpg {

//--------------------------------------------------------------------------------------------------

Cube::Cube(int depth, int width)
    :
    m_depth(depth),
    m_width(width),
    m_move(false)
{
    m_amount = depth * width;
    m_total_indices = 36;
    m_total_vertices = 8;

    //setup shader
    m_shader.load_from_file(GL_VERTEX_SHADER, "shader/simple_vertex.glsl");
    m_shader.load_from_file(GL_FRAGMENT_SHADER, "shader/simple_fragment.glsl");
    m_shader.create_link_program();
    m_shader.use();
        m_shader.add_attribute("vVertex");
        m_shader.add_uniform("MVP");
        m_shader.add_uniform("depth");
        m_shader.add_uniform("width");
        m_shader.add_uniform("time");
        m_shader.add_uniform("move");
    m_shader.un_use();

    init();
}

//--------------------------------------------------------------------------------------------------

Cube::~Cube()
{
    destroy();
}

//--------------------------------------------------------------------------------------------------

void
Cube::time(float time)
{
    m_time = time;
}

//--------------------------------------------------------------------------------------------------

void
Cube::move(bool move)
{
    m_move = move;
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
Cube::set_custom_uniforms()
{
    glUniform1i(m_shader("depth"), m_depth);
    glUniform1i(m_shader("width"), m_width);
    glUniform1f(m_shader("time"), m_time);
    glUniform1i(m_shader("move"), m_move);
}

//--------------------------------------------------------------------------------------------------

} // namespace arrrpg
