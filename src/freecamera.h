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

#ifndef _FREECAMERA_H_
#define _FREECAMERA_H_

#include "camera.h"

namespace arrrpg {

class FreeCamera : public Camera
{
public:
    FreeCamera(void);
    ~FreeCamera(void);

    void walk(const float amount);
    void strafe(const float amount);
    void lift(const float amount);

public: // from Camera
    void update();
    void rotate(const float yaw, const float pitch, const float roll);

protected:
    float m_yaw;
    float m_pitch;
    float m_roll;

    glm::vec3 m_translation;
};

}

#endif //_FREECAMERA_H_
