#pragma once

#include <gl/glew.h>

namespace Danburite
{
	enum class MaterialOptionFlag : GLuint
	{
		NONE				= 0U,

		LIGHTING			= 0b0000'0000'0000'0001U,
		AMBIENT_TEXTURE		= 0b0000'0000'0000'0010U,
		SPECULAR_TEXTURE	= 0b0000'0000'0000'0100U,
		SHININESS_TEXTURE	= 0b0000'0000'0000'1000U,
		ALPHA_TEXTURE		= 0b0000'0000'0001'0000U,
		NORMAL_TEXTURE		= 0b0000'0000'0010'0000U
	};

	constexpr MaterialOptionFlag operator|(const MaterialOptionFlag lhs, const MaterialOptionFlag rhs)
	{
		return MaterialOptionFlag(GLuint(lhs) | GLuint(rhs));
	}

	constexpr MaterialOptionFlag operator~(const MaterialOptionFlag flag) noexcept
	{
		return MaterialOptionFlag(~GLuint(flag));
	}

	constexpr MaterialOptionFlag &operator|=(MaterialOptionFlag &lhs, const MaterialOptionFlag rhs)
	{
		reinterpret_cast<GLuint &>(lhs) |= GLuint(rhs);
		return lhs;
	}

	constexpr MaterialOptionFlag &operator&=(MaterialOptionFlag &lhs, const MaterialOptionFlag rhs)
	{
		reinterpret_cast<GLuint &>(lhs) &= GLuint(rhs);
		return lhs;
	}
}
