#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class RasterizationType : GLenum
	{
		POINT = GL_POINT,
		LINE = GL_LINE,
		FILL = GL_FILL
	};
}