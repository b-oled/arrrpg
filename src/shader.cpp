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

//--------------------------------------------------------------------------------------------------

namespace arrrpg {

//--------------------------------------------------------------------------------------------------

Shader::Shader()
{

}

//--------------------------------------------------------------------------------------------------

Shader::~Shader()
{
    m_attributeList.clear();
    m_uniformLocationList.clear();
}

//--------------------------------------------------------------------------------------------------

void
Shader::load_from_string(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);
    const char* foo = source.c_str();
    glShaderSource(shader, 1, &foo, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = (GLchar*)calloc(length, sizeof(GLchar));
        glGetShaderInfoLog(shader, length, NULL, info);
        fprintf(stderr, "glCompileShader failed:\n%s\n", info);
        free(info);
    }
    switch (type)
    {
    case GL_VERTEX_SHADER:
        m_vertex_shader = shader;
        break;
    case GL_FRAGMENT_SHADER:
        m_fragment_shader = shader;
        break;
    case GL_GEOMETRY_SHADER:
        m_geometry_shader = shader;
        break;
    default:
        break;
    }
}

//--------------------------------------------------------------------------------------------------

void
Shader::load_from_file(GLenum type, const std::string &filename)
{
    std::ifstream fp;
    fp.open(filename.c_str(), std::ios_base::in);
    if(fp) {
        std::string line, buffer;
        while(getline(fp, line)) {
            buffer.append(line);
            buffer.append("\r\n");
        }
        //copy to source
        load_from_string(type, buffer);
    } else {
        std::cerr << "Error loading shader: " << filename << std::endl;
    }
}

//--------------------------------------------------------------------------------------------------

void
Shader::create_link_program() {
    m_program = glCreateProgram ();
    if (m_vertex_shader != 0)
    {
        glAttachShader(m_program, m_vertex_shader);
    }
    if (m_fragment_shader != 0)
    {
        glAttachShader(m_program, m_fragment_shader);
    }
    if (m_geometry_shader != 0)
    {
        glAttachShader(m_program, m_geometry_shader);
    }

    //link and check whether the program links fine
    GLint status;
    glLinkProgram (m_program);
    glGetProgramiv (m_program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint length;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = (GLchar*)calloc(length, sizeof(GLchar));
        glGetProgramInfoLog(m_program, length, NULL, info);
        fprintf(stderr, "glLinkProgram failed:\n%s\n", info);
        free(info);
    }
    glDeleteShader(m_vertex_shader);
    glDeleteShader(m_fragment_shader);
    glDeleteShader(m_geometry_shader);
}

//--------------------------------------------------------------------------------------------------

void
Shader::use()
{
    glUseProgram(m_program);
}

//--------------------------------------------------------------------------------------------------

void
Shader::un_use()
{
    glUseProgram(0);
}

//--------------------------------------------------------------------------------------------------

void
Shader::add_attribute(const std::string& attribute)
{
    m_attributeList[attribute] = glGetAttribLocation(m_program, attribute.c_str());
}

//--------------------------------------------------------------------------------------------------

GLuint
Shader::operator [](const std::string& attribute)
{
    return m_attributeList[attribute];
}

//--------------------------------------------------------------------------------------------------

void
Shader::add_uniform(const std::string& uniform)
{
    m_uniformLocationList[uniform] = glGetUniformLocation(m_program, uniform.c_str());
}

//--------------------------------------------------------------------------------------------------

GLuint
Shader::operator()(const std::string& uniform)
{
    return m_uniformLocationList[uniform];
}

//--------------------------------------------------------------------------------------------------

void
Shader::delete_program()
{
    glDeleteProgram(m_program);
}

//--------------------------------------------------------------------------------------------------

} // arrrpg
