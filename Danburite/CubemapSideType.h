#pragma once

#include <gl/glew.h>

namespace ObjectGL
{
	enum class CubemapSideType : GLenum
	{
		POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	constexpr CubemapSideType operator+(const CubemapSideType lhs, const unsigned rhs)
	{
		return CubemapSideType(unsigned(lhs) + rhs);
	}
}
