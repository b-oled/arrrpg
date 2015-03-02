// arrrpg - runtime.h
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

#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include "stdinc.h"
#include "shader.h"

namespace arrrpg {

template <typename Impl>
class Renderable {
public:

    void render(const float* MVP)
    {
        shader.Use();
            glUniformMatrix4fv(shader("MVP"), 1, GL_FALSE, MVP);
            SetCustomUniforms();
            glBindVertexArray(vaoID);
                glDrawElements(primType, totalIndices, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        shader.UnUse();
    }

    int total_vertices()
    {
        return impl().total_vertices();
    }

    int total_indices()
    {
        return impl().total_indices();
    }

    GLenum primitive_type()
    {
        return impl().primitive_type();
    }

    void fill_vertex_buffer(GLfloat* pBuffer)
    {
        return impl().fill_vertex_buffer(pBuffer);
    }

    void fill_index_buffer(GLuint* pBuffer)
    {
        return impl().fill_index_buffer(pBuffer);
    }

    void SetCustomUniforms()
    {
        return impl().SetCustomUniforms();
    }

    void init()
    {
        glGenVertexArrays(1, &vaoID);
        glGenBuffers(1, &vboVerticesID);
        glGenBuffers(1, &vboIndicesID);

        //get total vertices and indices
        totalVertices = total_vertices();
        totalIndices  = total_indices();
        primType      = primitive_type();

        //now allocate buffers
        glBindVertexArray(vaoID);

        glBindBuffer (GL_ARRAY_BUFFER, vboVerticesID);
        glBufferData (GL_ARRAY_BUFFER, totalVertices * sizeof(glm::vec3), 0, GL_STATIC_DRAW);

        GLfloat* pBuffer = static_cast<GLfloat*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        fill_vertex_buffer(pBuffer);
        glUnmapBuffer(GL_ARRAY_BUFFER);

        glEnableVertexAttribArray(shader["vVertex"]);
        glVertexAttribPointer(shader["vVertex"], 3, GL_FLOAT, GL_FALSE,0,0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndicesID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalIndices * sizeof(GLuint), 0, GL_STATIC_DRAW);

        GLuint* pIBuffer = static_cast<GLuint*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,
                                                            GL_WRITE_ONLY));
        fill_index_buffer(pIBuffer);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

        glBindVertexArray(0);
    }

    void destroy()
    {
        //Destroy shader
        shader.DeleteShaderProgram();

        //Destroy vao and vbo
        glDeleteBuffers(1, &vboVerticesID);
        glDeleteBuffers(1, &vboIndicesID);
        glDeleteVertexArrays(1, &vaoID);
    }

private:
    Impl& impl()
    {
        return *static_cast<Impl*>(this);
    }

protected:
    GLuint vaoID;
    GLuint vboVerticesID;
    GLuint vboIndicesID;

    Shader shader;

    GLenum primType;
    int totalVertices, totalIndices;

};

} // namespace arrrpg

#endif // _RENDERABLE_H_
