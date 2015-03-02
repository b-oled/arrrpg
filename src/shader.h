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

#ifndef _SHADER_H_
#define _SHADER_H_

#include "stdinc.h"
#include <map>
#include <stdlib.h>

namespace arrrpg {

class Shader
{
public:
    Shader(void);
    ~Shader(void);

    void LoadFromString(GLenum type, const std::string& source);
    void LoadFromFile(GLenum type, const std::string& filename);
    void CreateAndLinkProgram();
    void Use();
    void UnUse();
    void AddAttribute(const std::string& attribute);
    void AddUniform(const std::string& uniform);
    GLuint operator[](const std::string& attribute);
    GLuint operator()(const std::string& uniform);
    void DeleteShaderProgram();

private:
    GLuint m_program;
    GLuint m_vertex_shader;
    GLuint m_fragment_shader;
    GLuint m_geometry_shader;
    std::map<std::string,GLuint> m_attributeList;
    std::map<std::string,GLuint> m_uniformLocationList;
};

} // arrrpg

#endif // _SHADER_H_
