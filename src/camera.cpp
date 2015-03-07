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

#include "camera.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

//--------------------------------------------------------------------------------------------------

namespace arrrpg {

//--------------------------------------------------------------------------------------------------

glm::vec3 Camera::UP = glm::vec3(0,1,0);

//--------------------------------------------------------------------------------------------------

Camera::Camera()
{

}

//--------------------------------------------------------------------------------------------------

Camera::~Camera()
{

}

//--------------------------------------------------------------------------------------------------

void
Camera::setup_projection(const float fovy, const float aspect_ratio)
{
    m_P = glm::perspective(fovy, aspect_ratio, 0.1f, 1000.0f);
    m_fov = fovy;
    m_aspect_ratio = aspect_ratio;
}

//--------------------------------------------------------------------------------------------------

const glm::mat4
Camera::view_matrix() const
{
    return m_V;
}

//--------------------------------------------------------------------------------------------------

const glm::mat4
Camera::projection_matrix() const
{
    return m_P;
}

//--------------------------------------------------------------------------------------------------

void
Camera::position(const glm::vec3 position)
{
    m_position = position;
}

//--------------------------------------------------------------------------------------------------

const glm::vec3
Camera::position() const
{
    return m_position;
}

//--------------------------------------------------------------------------------------------------

glm::mat4
Camera::get_matrix_using_yaw_pitch_roll(const float yaw, const float pitch, const float roll)
{
    glm::mat4 R = glm::mat4(1);

    R = glm::rotate(R, roll, glm::vec3(0,0,1));
    R = glm::rotate(R,  yaw, glm::vec3(0,1,0));
    R = glm::rotate(R, pitch, glm::vec3(1,0,0));

    return R;
}

//--------------------------------------------------------------------------------------------------

float
Camera::get_FOV() const
{
    return m_fov;
}

//--------------------------------------------------------------------------------------------------

float
Camera::get_aspect_ratio() const
{
    return m_aspect_ratio;
}

//--------------------------------------------------------------------------------------------------

}

