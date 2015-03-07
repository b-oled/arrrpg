// arrrpg - helper.h
// Copyright (C) 2015 Ole Diederich <ole@rumgespinne.com>
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

#ifndef __HELPER_H__
#define __HELPER_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* path);
GLuint create_shader(GLenum type, const char* source);
GLuint load_shader(GLenum type, const char* path);
GLuint create_program( const char* vs_path, const char* fs_path);
GLuint make_buffer(GLsizei vsize, const GLfloat* vdata,
                GLsizei isize, const GLushort* idata,
                const GLuint *position, GLuint vao);

#endif // __HELPER_H__
