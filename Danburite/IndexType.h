#pragma once

#include <GL/glew.h>

namespace ObjectGL
{
	enum class IndexType : GLenum
	{
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		UNSIGNED_INT = GL_UNSIGNED_INT
	};

	constexpr GLsizei indexSize(const IndexType type) noexcept
	{
		switch (type)
		{
		case IndexType::UNSIGNED_BYTE:
			return 1;

		case IndexType::UNSIGNED_SHORT:
			return 2;

		case IndexType::UNSIGNED_INT:
			return 4;
		}

		return 0;
	}
}
