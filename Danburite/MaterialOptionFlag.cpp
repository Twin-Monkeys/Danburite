#include "MaterialOptionFlag.h"

namespace Danburite
{
	MaterialOptionFlag &operator|=(MaterialOptionFlag &lhs, const MaterialOptionFlag rhs)
	{
		reinterpret_cast<GLuint &>(lhs) |= GLuint(rhs);
		return lhs;
	}

	MaterialOptionFlag &operator&=(MaterialOptionFlag &lhs, const MaterialOptionFlag rhs)
	{
		reinterpret_cast<GLuint &>(lhs) &= GLuint(rhs);
		return lhs;
	}
}