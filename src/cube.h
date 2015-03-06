// arrrpg - cube.h
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

#ifndef _CUBE_H_
#define _CUBE_H_

#include "renderable.h"

namespace arrrpg {

class Cube : public Renderable< Cube >
{

public:
    Cube(int rows, int cols);
    ~Cube();

    // from Renderable
    GLenum primitive_type();
    void fill_vertex_buffer(GLfloat* pBuffer);
    void fill_index_buffer(GLshort* pBuffer);
    void SetCustomUniforms();

private:
    int m_rows;
    int m_cols;

};

}

#endif // _CUBE_H_
