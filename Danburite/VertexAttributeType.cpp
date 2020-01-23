#include "VertexAttributeType.h"

namespace Danburite
{
	VertexAttributeType &operator|=(VertexAttributeType &lhs, const VertexAttributeFlag rhs)
	{
		reinterpret_cast<unsigned &>(lhs) |= unsigned(rhs);
		return lhs;
	}
}