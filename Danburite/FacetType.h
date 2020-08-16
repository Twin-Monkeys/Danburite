#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class FacetType : GLenum
	{
		FRONT = GL_FRONT,
		BACK = GL_BACK,
		FRONT_AND_BACK = GL_FRONT_AND_BACK
	};
}