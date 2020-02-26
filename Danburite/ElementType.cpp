#include "ElementType.h"
#include <cassert>

namespace ObjectGL
{
	GLsizei elementSize(const ElementType type) noexcept
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

		assert(false);
		return 0;
	}
}
