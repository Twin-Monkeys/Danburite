#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class RenderTargetType : GLenum
	{
		NONE = GL_NONE,
		FRONT_LEFT = GL_FRONT_LEFT,
		FRONT_RIGHT = GL_FRONT_RIGHT,
		BACK_LEFT = GL_BACK_LEFT,
		BACK_RIGHT = GL_BACK_RIGHT,
		FRONT = GL_FRONT,
		BACK = GL_BACK,
		LEFT = GL_LEFT,
		RIGHT = GL_RIGHT,
		FRONT_AND_BACK = GL_FRONT_AND_BACK
	};
}