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

World::World(int numx, int numz)
{
    m_numx = numx;
    m_numz = numz;

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

World::~World()
{
    destroy();
}

//--------------------------------------------------------------------------------------------------

void
World::time(float time)
{
    m_time = time;
}

//--------------------------------------------------------------------------------------------------

int
World::total_vertices()
{
    return (m_numx + 1) * (m_numz + 1);
}

//--------------------------------------------------------------------------------------------------

int
World::total_indices()
{
    return m_numx * m_numz * 2 * 3;
}

//--------------------------------------------------------------------------------------------------

GLenum
World::primitive_type()
{
    return GL_TRIANGLES;
}

//--------------------------------------------------------------------------------------------------

void
World::fill_vertex_buffer(GLfloat *pBuffer)
{
    glm::vec3* vertices = (glm::vec3*)(pBuffer);
    int count = 0;
    int i=0, j=0;
    for( j=0;j<=m_numz;j++) {
        for( i=0;i<=m_numx;i++) {
            vertices[count++] = glm::vec3( ((float(i)/(m_numx-1)) *2-1)*2, 0, ((float(j)/(m_numz-1))*2-1)*2);
        }
    }
}

//--------------------------------------------------------------------------------------------------

void
World::fill_index_buffer(GLshort *pBuffer)
{
    int i=0, j=0;
    GLshort* id=pBuffer;
    for (i = 0; i < m_numz; i++) {
        for (j = 0; j < m_numx; j++) {
            int i0 = i * (m_numx+1) + j;
            int i1 = i0 + 1;
            int i2 = i0 + (m_numx+1);
            int i3 = i2 + 1;
            if ((j+i)%2) {
                *id++ = i0; *id++ = i2; *id++ = i1;
                *id++ = i1; *id++ = i2; *id++ = i3;
            } else {
                *id++ = i0; *id++ = i2; *id++ = i3;
                *id++ = i0; *id++ = i3; *id++ = i1;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------

void
World::SetCustomUniforms()
{
    glUniform1f(shader("time"), m_time);
}

//--------------------------------------------------------------------------------------------------

} // namespace arrrpg
