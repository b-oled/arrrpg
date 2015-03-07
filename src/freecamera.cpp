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

#include "freecamera.h"
#include <glm/gtc/matrix_transform.hpp>

//--------------------------------------------------------------------------------------------------

namespace arrrpg {

//--------------------------------------------------------------------------------------------------

FreeCamera::FreeCamera()
{
    m_translation = glm::vec3(0);
}

//--------------------------------------------------------------------------------------------------

FreeCamera::~FreeCamera(void)
{
}

//--------------------------------------------------------------------------------------------------

void
FreeCamera::update()
{
    glm::mat4 R = get_matrix_using_yaw_pitch_roll(m_yaw,m_pitch,m_roll);
    m_position += m_translation;
    m_translation = glm::vec3(0);

    m_look = glm::vec3(R*glm::vec4(0,0,1,0));
    glm::vec3 tgt = m_position + m_look;
    m_up = glm::vec3(R*glm::vec4(0,1,0,0));
    m_right = glm::cross(m_look, m_up);
    m_V = glm::lookAt(m_position, tgt, m_up);

    //normalize
    //look = glm::normalize(look);
    //up = glm::normalize(up);
    //right = glm::normalize(right);
}

//--------------------------------------------------------------------------------------------------

void
FreeCamera::rotate(const float yaw, const float pitch, const float roll)
{
    m_yaw = yaw;
    m_pitch = pitch;
    m_roll = roll;
}

//--------------------------------------------------------------------------------------------------

void
FreeCamera::walk(const float amount)
{
    m_translation += (m_look * amount);
}

//--------------------------------------------------------------------------------------------------

void
FreeCamera::strafe(const float amount)
{
    m_translation += (m_right * amount);
}

//--------------------------------------------------------------------------------------------------

void
FreeCamera::lift(const float amount)
{
    m_translation += (m_up * amount);
}

//--------------------------------------------------------------------------------------------------

} // arrrpg
