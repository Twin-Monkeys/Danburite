#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class WindingOrderType : GLenum
	{
		COUNTER_CLOCKWISE = GL_CCW,
		CLOCKWISE = GL_CW
	};
}