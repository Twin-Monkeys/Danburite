#pragma once

#include <GL/glew.h>
#include <cassert>

namespace ObjectGL
{
	enum class IndexType : GLenum
	{
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		UNSIGNED_INT = GL_UNSIGNED_INT
	};

	GLsizei indexSize(const IndexType type) noexcept;
}
