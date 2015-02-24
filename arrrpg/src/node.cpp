// arrrpg - node.cpp
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

#include "node.h"

#include <GL/gl.h>

//--------------------------------------------------------------------------------------------------

namespace arrrpg {

//--------------------------------------------------------------------------------------------------

Node::Node(Node *parent)
    :
    m_parent( parent )
{
    m_mtransform = new GLfloat[16]{
      1, 0, 0, 0,
      0, 1, 0, 0,
      0.5, 0, 1, 0.5,
      0, 0, 0, 1
    };
}

//--------------------------------------------------------------------------------------------------

void
Node::draw()
{
    // TODO: push/pop matric deprecated need to apply matrix
    glPushMatrix();
    this->do_draw();

    for(auto&& node : m_children)
    {
        node->draw();
    }
    glPopMatrix();
}

//--------------------------------------------------------------------------------------------------

} // namespace arrrpg
