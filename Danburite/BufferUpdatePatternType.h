#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class BufferUpdatePatternType : GLenum
	{
		STREAM = GL_STREAM_DRAW,
		STATIC = GL_STATIC_DRAW,
		DYNAMIC = GL_DYNAMIC_DRAW
	};
}
