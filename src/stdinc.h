#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <assert.h>
#include <new>

namespace arrrpg {

#define ARRRPG_ASSERT( x ) assert( x )
#define ARRRPG_UNUSED( x ) (void)( x )
#define ARRRPG_NEW( x ) new (std::nothrow) x;
#define ARRRPG_CHECK_GL_ERROR assert( glGetError() == GL_NO_ERROR )

}
