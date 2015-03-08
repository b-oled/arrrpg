// arrrpg - Camera.h
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

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "stdinc.h"
#include <glm/glm.hpp>

namespace arrrpg {

class Camera
{
public:
    Camera(void);
    ~Camera(void);

    void setup_projection(const float fovy=45.0f, const float aspect_ratio=1.33333f);

    virtual void update() = 0;
    virtual void rotate(const float yaw, const float pitch, const float roll) = 0;
    //virtual void Translate(const float dx, const float dy, const float dz) = 0;

    const glm::mat4 view_matrix() const;
    const glm::mat4 projection_matrix() const;

    void position(const glm::vec3 v);
    const glm::vec3 position() const;

    glm::mat4 get_matrix_using_yaw_pitch_roll(const float yaw, const float pitch, const float roll);

    float get_FOV() const;
    float get_aspect_ratio() const;

protected:
    float m_fov;
    float m_aspect_ratio;
    static glm::vec3 UP;
    glm::vec3 m_look;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_position;
    glm::mat4 m_V;
    glm::mat4 m_P;
};

}

#endif //_CAMERA_H_
