#include "IndexType.h"

namespace ObjectGL
{
	GLsizei indexSize(const IndexType type) noexcept
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

		assert(false);
		return 0;
	}
}