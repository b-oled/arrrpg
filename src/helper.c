// arrrpg - helper.c
// Copyright (C) 2015 Ole Diederich <ole@rumgespinne.com>
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

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "helper.h"

char*
read_file(const char* path) {
    FILE* fp = fopen(path, "rb");
    fseek(fp , 0L , SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    char* content = calloc(1 , size + 1);
    fread(content, size, 1, fp);
    fclose(fp);

    return content;
}

GLuint
create_shader(GLenum type, const char* source) {
    GLuint shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &source, NULL);
    glCompileShader(shader_id);

    // check and log result of compilation
    GLint result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        GLsizei log_length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar* log = calloc(1, log_length + 1);
        glGetShaderInfoLog(shader_id, log_length, NULL, log);
        fprintf(stderr, "glCompileShader failed: %s\n", log);
        free(log);
    }

    return shader_id;
}

GLuint
load_shader(GLenum type, const char* path) {
    char* source = read_file(path);
    GLuint shader = create_shader(type, source);
    free(source);

    return shader;
}

GLuint
create_program( const char* vs_path, const char* fs_path) {
    GLuint vs_id = load_shader(GL_VERTEX_SHADER, vs_path);
    GLuint fs_id = load_shader(GL_FRAGMENT_SHADER, fs_path);
    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vs_id);
    glAttachShader(program_id, fs_id);
    glLinkProgram(program_id);

    // check and log result of linking
    GLint result;
    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        GLsizei log_length;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar* log = calloc(1, log_length + 1);
        glGetProgramInfoLog(program_id, log_length, NULL, log);
        fprintf(stderr, "glLinkProgram failed: %s\n", log);
        free(log);
    }
    glDetachShader(program_id, vs_id);
    glDetachShader(program_id, fs_id);
    glDeleteShader(vs_id);
    glDeleteShader(fs_id);

    return program_id;
}

GLuint
make_buffer(GLsizei vsize, const GLfloat* vdata,
            GLsizei isize, const GLushort* idata,
            const GLuint* position, GLuint vao) {
    GLuint vertices_id;
    GLuint indices_id;

    glGenBuffers(1, &vertices_id);
    glGenBuffers(1, &indices_id);

    glBindVertexArray(vao);

    glBindBuffer (GL_ARRAY_BUFFER, vertices_id);
    glBufferData (GL_ARRAY_BUFFER, vsize * sizeof(GLfloat), 0, GL_STATIC_DRAW);

    GLfloat* pBuffer = (GLfloat*)(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    memcpy(pBuffer, vdata, vsize );
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glEnableVertexAttribArray(position);
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_id * sizeof(GLshort), 0, GL_STATIC_DRAW);

    GLshort* pIBuffer = (GLshort*)(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,
                                                          GL_WRITE_ONLY));
    memcpy(pIBuffer, idata, isize );
    glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

    glBindVertexArray(0);
}
