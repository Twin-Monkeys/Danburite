#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>

namespace ObjectGL
{
	enum class GLProfileFlag : unsigned
	{
		CORE_PROFILE = WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		COMPATIBILITY_PROFILE = WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
	};

	constexpr GLProfileFlag operator|(const GLProfileFlag lhs, const GLProfileFlag rhs) noexcept
	{
		return GLProfileFlag(unsigned(lhs) | unsigned(rhs));
	}

	constexpr GLProfileFlag operator~(const GLProfileFlag flag) noexcept
	{
		return GLProfileFlag(~unsigned(flag));
	}

	constexpr int &operator|=(int &lhs, const GLProfileFlag rhs) noexcept
	{
		lhs |= int(rhs);
		return lhs;
	}

	constexpr int &operator&=(int &lhs, const GLProfileFlag rhs) noexcept
	{
		lhs &= int(rhs);
		return lhs;
	}
}
