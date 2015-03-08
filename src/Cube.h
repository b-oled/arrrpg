// arrrpg - Cube.h
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

#include "Entity.h"

namespace arrrpg {

class Cube : public Entity
{

public:
    Cube(int depth, int width);
    ~Cube();

    void time(float time);
    void move(bool move);

    // from Entity
    GLenum primitive_type();
    void fill_vertex_buffer(GLfloat* pBuffer);
    void fill_index_buffer(GLshort* pBuffer);
    void set_custom_uniforms();

private:
    int m_depth;
    int m_width;
    float m_time;
    bool m_move;
};

}

#endif // _CUBE_H_
