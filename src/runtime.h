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

#ifndef _RUNTIME_H_
#define _RUNTIME_H_

#include "world.h"

struct GLFWwindow;

namespace arrrpg {

class Runtime
{

public:
    Runtime();
    ~Runtime();

    void start();

private:
    GLFWwindow* m_window;
    Renderable< World >* m_world;

};

}

#endif // _RUNTIME_H_
