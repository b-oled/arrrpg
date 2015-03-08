// arrrpg - Entity.h
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

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "stdinc.h"
#include "Shader.h"

namespace arrrpg {

class Entity {

public:

    void render(const float* MVP);
    void init();
    void destroy();

protected:
    virtual GLenum primitive_type() = 0;
    virtual void fill_vertex_buffer(GLfloat* pBuffer) = 0;
    virtual void fill_index_buffer(GLshort* pBuffer) = 0;
    virtual void set_custom_uniforms() = 0;

    GLuint m_vao_id;
    GLuint m_vbo_vertices_id;
    GLuint m_vbo_indices_id;

    Shader m_shader;

    GLenum m_primitive_type;
    int m_total_vertices;
    int m_total_indices;
    int m_amount;

};

} // namespace arrrpg

#endif // _ENTITY_H_
