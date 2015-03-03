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

#include "stdinc.h"
#include "world.h"

struct GLFWwindow;

namespace arrrpg {

class Runtime
{

public:
    Runtime();
    ~Runtime();
    void start();

    // glfw callbacks
    void on_viewport_resize(int w, int h);

private:
    GLFWwindow* m_window;
    World* m_world;
    glm::mat4 m_P;

    // glfw callback wrapper
    inline static auto glfw_fb_size_callback(
            GLFWwindow *window,
            int w,
            int h) -> void {
        Runtime* runtime = static_cast<Runtime*>(glfwGetWindowUserPointer(window));
        runtime->on_viewport_resize(w, h);
    }

};

}

#endif // _RUNTIME_H_
