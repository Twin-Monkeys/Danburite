#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class BufferAccessType : GLenum
	{
		READ_ONLY = GL_READ_ONLY,
		WRITE_ONLY = GL_WRITE_ONLY,
		READ_WRITE = GL_READ_WRITE
	};
}