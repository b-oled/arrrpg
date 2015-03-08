// arrrpg - Entity.cpp
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

#include "Entity.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>

//--------------------------------------------------------------------------------------------------

namespace arrrpg {

//--------------------------------------------------------------------------------------------------

void
Entity::render(const float *MVP)
{
    m_shader.use();
        glUniformMatrix4fv(m_shader("MVP"), 1, GL_FALSE, MVP);
        set_custom_uniforms();
        glBindVertexArray(m_vao_id);
            glDrawElementsInstanced(m_primitive_type,
                                    m_total_indices,
                                    GL_UNSIGNED_SHORT,
                                    0,
                                    m_amount);
        glBindVertexArray(0);
    m_shader.un_use();
}

//--------------------------------------------------------------------------------------------------

void
Entity::init()
{
    glGenVertexArrays(1, &m_vao_id);
    glGenBuffers(1, &m_vbo_vertices_id);
    glGenBuffers(1, &m_vbo_indices_id);

    //get total vertices and indices
    m_primitive_type = primitive_type();

    //now allocate buffers
    glBindVertexArray(m_vao_id);

        glBindBuffer (GL_ARRAY_BUFFER, m_vbo_vertices_id);
        glBufferData (GL_ARRAY_BUFFER, m_total_vertices * sizeof(glm::vec3), 0, GL_STATIC_DRAW);

        GLfloat* pBuffer = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        fill_vertex_buffer(pBuffer);
        glUnmapBuffer(GL_ARRAY_BUFFER);

        glEnableVertexAttribArray(m_shader["vVertex"]);
        glVertexAttribPointer(m_shader["vVertex"], 3, GL_FLOAT, GL_FALSE,0,0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo_indices_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_total_indices * sizeof(GLshort), 0, GL_STATIC_DRAW);

        GLshort* pIBuffer = static_cast<GLshort*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,
                                                              GL_WRITE_ONLY));
        fill_index_buffer(pIBuffer);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

    glBindVertexArray(0);
}

//--------------------------------------------------------------------------------------------------

void
Entity::destroy()
{
    //Destroy shader
    m_shader.delete_program();

    //Destroy vao and vbo
    glDeleteBuffers(1, &m_vbo_vertices_id);
    glDeleteBuffers(1, &m_vbo_indices_id);
    glDeleteVertexArrays(1, &m_vao_id);
}

//--------------------------------------------------------------------------------------------------

} // arrrpg
