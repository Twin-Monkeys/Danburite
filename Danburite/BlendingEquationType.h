#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class BlendingEquationType : GLenum
	{
		ADD = GL_FUNC_ADD,
		SUBTRACT = GL_FUNC_SUBTRACT,
		REVERSE_SUBTRACT = GL_FUNC_REVERSE_SUBTRACT,
		MIN = GL_MIN,
		MAX = GL_MAX
	};
}
