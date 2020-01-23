#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class BlendingEquationType : GLenum
	{
		FUNC_ADD = GL_FUNC_ADD,
		FUNC_SUBTRACT = GL_FUNC_SUBTRACT,
		FUNC_REVERSE_SUBTRACT = GL_FUNC_REVERSE_SUBTRACT,
		MIN = GL_MIN,
		MAX = GL_MAX
	};
}
