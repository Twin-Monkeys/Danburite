#include "GLProfileFlag.h"

namespace ObjectGL
{
	int &operator|=(int &lhs, const GLProfileFlag rhs) noexcept
	{
		lhs |= int(rhs);
		return lhs;
	}

	int &operator&=(int &lhs, const GLProfileFlag rhs) noexcept
	{
		lhs &= int(rhs);
		return lhs;
	}
}