// arrrpg - shader.h
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

#include "shader.h"
#include "stdinc.h"
#include <sstream>
#include <fstream>
#include <iostream>

namespace arrrpg {

void
Shader::LoadFromString(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);
    const char* foo = source.c_str();
    glShaderSource(shader, 1, &foo, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = (GLchar*)calloc(length, sizeof(GLchar));
        glGetShaderInfoLog(shader, length, NULL, info);
        fprintf(stderr, "glCompileShader failed:\n%s\n", info);
        free(info);
    }
    m_shaders[m_totalShaders++] = shader;
}

void
Shader::LoadFromFile(GLenum type, const std::string &filename)
{
    std::ifstream f(filename);
    std::string str;
    str.assign(std::istreambuf_iterator<char>(f),
                    std::istreambuf_iterator<char>());
    LoadFromString(type, str);
}

void Shader::CreateAndLinkProgram() {
    m_program = glCreateProgram ();
    if (m_shaders[VERTEX_SHADER] != 0) {
        glAttachShader (m_program, m_shaders[VERTEX_SHADER]);
    }
    if (m_shaders[FRAGMENT_SHADER] != 0) {
        glAttachShader (m_program, m_shaders[FRAGMENT_SHADER]);
    }
    if (m_shaders[GEOMETRY_SHADER] != 0) {
        glAttachShader (m_program, m_shaders[GEOMETRY_SHADER]);
    }

    //link and check whether the program links fine
    GLint status;
    glLinkProgram (m_program);
    glGetProgramiv (m_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;

        glGetProgramiv (m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog= new GLchar[infoLogLength];
        glGetProgramInfoLog (m_program, infoLogLength, NULL, infoLog);
        std::cerr<<"Link log: "<<infoLog<<std::endl;
        delete [] infoLog;
    }

    glDeleteShader(m_shaders[VERTEX_SHADER]);
    glDeleteShader(m_shaders[FRAGMENT_SHADER]);
    glDeleteShader(m_shaders[GEOMETRY_SHADER]);
}

void Shader::Use() {
    glUseProgram(m_program);
}

void Shader::UnUse() {
    glUseProgram(0);
}

void Shader::AddAttribute(const std::string& attribute) {
    m_attributeList[attribute]= glGetAttribLocation(m_program, attribute.c_str());
}

//An indexer that returns the location of the attribute
GLuint Shader::operator [](const std::string& attribute) {
    return m_attributeList[attribute];
}

void Shader::AddUniform(const std::string& uniform) {
    m_uniformLocationList[uniform] = glGetUniformLocation(m_program, uniform.c_str());
}

GLuint Shader::operator()(const std::string& uniform){
    return m_uniformLocationList[uniform];
}


} // arrrpg
