#pragma once

#include <GL/glew.h>
#include <unordered_map>

namespace ObjectGL
{
	enum class ElementType : GLenum
	{
		BYTE = GL_BYTE,
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		SHORT = GL_SHORT,
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		INT = GL_INT,
		UNSIGNED_INT = GL_UNSIGNED_INT,
		HALF_FLOAT = GL_HALF_FLOAT,
		FLOAT = GL_FLOAT,
		DOUBLE = GL_DOUBLE,
		FIXED = GL_FIXED,
		INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
		UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
		UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV,
	};

	constexpr GLsizei elementSize(const ElementType type) noexcept
	{
		switch (type)
		{
		case ElementType::BYTE:
			[[fallthrough]];

		case ElementType::UNSIGNED_BYTE:
			return 1;

		case ElementType::SHORT:
			[[fallthrough]];

		case ElementType::UNSIGNED_SHORT:
			[[fallthrough]];

		case ElementType::HALF_FLOAT:
			return 2;

		case ElementType::INT:
			[[fallthrough]];

		case ElementType::UNSIGNED_INT:
			[[fallthrough]];

		case ElementType::FLOAT:
			[[fallthrough]];

		case ElementType::INT_2_10_10_10_REV:
			[[fallthrough]];

		case ElementType::UNSIGNED_INT_2_10_10_10_REV:
			[[fallthrough]];

		case ElementType::UNSIGNED_INT_10F_11F_11F_REV:
			return 4;

		case ElementType::DOUBLE:
			return 8;
		}

		return 0;
	}
}
