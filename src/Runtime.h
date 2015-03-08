// arrrpg - Runtime.h
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
#include <memory>

struct GLFWwindow;

namespace arrrpg {

class World;
class Cube;
class FreeCamera;

class Runtime
{

public:
    Runtime();
    ~Runtime();
    void start();

    // glfw callbacks
    void on_viewport_resize(int w, int h);
    void on_key_callback(int key, int scancode, int action, int mods);
    void on_cursorpos_callback(double x, double y);
    void on_mousebtn_callback(int btn, int action, int mods);

private:
    GLFWwindow* m_window;
    std::unique_ptr< Cube > m_cube;
    std::unique_ptr< FreeCamera > m_camera;
    int m_width;
    int m_height;
    float m_dt;
    float m_last_time;
    float m_current_time;
    bool m_mouse_look;
    float m_mouse_oldx;
    float m_mouse_oldy;
    float m_fov;
    float m_rX;
    float m_rY;

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

    inline static auto glfw_mousepos_callback(
                GLFWwindow *window,
                double x, double y) -> void {
        Runtime* runtime = static_cast<Runtime*>(glfwGetWindowUserPointer(window));
        runtime->on_cursorpos_callback(x, y);
    }

    inline static auto glfw_mousebtn_callback(
                GLFWwindow *window,
                int btn, int action, int mods) -> void {
        Runtime* runtime = static_cast<Runtime*>(glfwGetWindowUserPointer(window));
        runtime->on_mousebtn_callback(btn, action, mods);
    }

};

}

#endif // _RUNTIME_H_
