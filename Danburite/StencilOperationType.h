#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class StencilOperationType : GLenum
	{
		KEEP = GL_KEEP,
		ZERO = GL_ZERO,
		REPLACE = GL_REPLACE,
		INCR = GL_INCR,
		INCR_WRAP = GL_INCR_WRAP,
		DECR = GL_DECR,
		DECR_WRAP = GL_DECR_WRAP,
		INVERT = GL_INVERT
	};
}