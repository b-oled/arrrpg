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

struct GLFWwindow;

namespace arrrpg {

class World;
class Cube;

class Runtime
{

public:
    Runtime();
    ~Runtime();
    void start();

    // glfw callbacks
    void on_viewport_resize(int w, int h);
    void on_key_callback(int key, int scancode, int action, int mods);

private:
    GLFWwindow* m_window;
    World* m_world;
    Cube* m_cube;
    glm::mat4 m_P;
    int m_width;
    int m_height;
    float m_camx;
    float m_camy;
    float m_camrZ;
    float m_camdist;

    // glfw callback wrapper
    inline static auto glfw_fb_size_callback(
            GLFWwindow *window,
            int w,
            int h) -> void {
        Runtime* runtime = static_cast<Runtime*>(glfwGetWindowUserPointer(window));
        runtime->on_viewport_resize(w, h);
    }

    inline static auto glfw_key_callback(
                GLFWwindow *window,
                int key, int scancode, int action, int mods) -> void {
        Runtime* runtime = static_cast<Runtime*>(glfwGetWindowUserPointer(window));
        runtime->on_key_callback(key, scancode, action, mods);
    }

};

}

#endif // _RUNTIME_H_
