// arrrpg - world.cpp
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

#include "world.h"

//--------------------------------------------------------------------------------------------------

namespace arrrpg {

//--------------------------------------------------------------------------------------------------

World::World(int width, int depth)
{
    m_width = width;
    m_depth = depth;

    //setup shader
    shader.LoadFromFile(GL_VERTEX_SHADER, "shaders/shader.vert");
    shader.LoadFromFile(GL_FRAGMENT_SHADER, "shaders/shader.frag");
    shader.CreateAndLinkProgram();
    shader.Use();
        shader.AddAttribute("vVertex");
        shader.AddUniform("MVP");
    shader.UnUse();

    init();
}

//--------------------------------------------------------------------------------------------------

World::~World()
{
    destroy();
}

//--------------------------------------------------------------------------------------------------

int
World::total_vertices()
{
    return ((m_width + 1) + (m_depth + 1)) * 2;
}

//--------------------------------------------------------------------------------------------------

int
World::total_indices()
{
    return (m_width * m_depth);
}

//--------------------------------------------------------------------------------------------------

GLenum
World::primitive_type()
{
    return GL_LINES;
}

//--------------------------------------------------------------------------------------------------

void
World::fill_vertex_buffer(GLfloat *pBuffer)
{
    glm::vec3* vertices = (glm::vec3*)(pBuffer);
    int count = 0;
    int width_2 = m_width/2;
    int depth_2 = m_depth/2;
    int i=0 ;

    for( i=-width_2;i<=width_2;i++)
    {
        vertices[count++] = glm::vec3( i,0,-depth_2);
        vertices[count++] = glm::vec3( i,0, depth_2);

        vertices[count++] = glm::vec3( -width_2,0,i);
        vertices[count++] = glm::vec3(  width_2,0,i);
    }
}

//--------------------------------------------------------------------------------------------------

void
World::fill_index_buffer(GLuint* pBuffer)
{
    int i=0;
    GLuint* id=pBuffer;
    for (i = 0; i < m_width * m_depth; i += 4)
    {
        *id++ = i;
        *id++ = i+1;
        *id++ = i+2;
        *id++ = i+3;
    }
}

//--------------------------------------------------------------------------------------------------

} // namespace arrrpg
