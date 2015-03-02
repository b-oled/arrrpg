#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <new>

namespace arrrpg {

#define ARRRPG_ASSERT( x ) assert( x )
#define ARRRPG_UNUSED( x ) (void)( x )
#define ARRRPG_NEW( x ) new (std::nothrow) x()

}
