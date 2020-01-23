#pragma once

#include <gl/glew.h>

namespace Danburite
{
	enum class MaterialOptionFlag : GLuint
	{
		NONE				= 0U,

		LIGHTING			= 0b0000'0000'0000'0001U,
		SHININESS_TEXTURE	= 0b0000'0000'0000'0010U,
		ALPHA_TEXTURE		= 0b0000'0000'0000'0100U,
		NORMAL_TEXTURE		= 0b0000'0000'0000'1000U
	};

	constexpr MaterialOptionFlag operator|(const MaterialOptionFlag lhs, const MaterialOptionFlag rhs)
	{
		return MaterialOptionFlag(GLuint(lhs) | GLuint(rhs));
	}

	constexpr MaterialOptionFlag operator~(const MaterialOptionFlag flag) noexcept
	{
		return MaterialOptionFlag(~GLuint(flag));
	}

	MaterialOptionFlag &operator|=(MaterialOptionFlag &lhs, const MaterialOptionFlag rhs);
	MaterialOptionFlag &operator&=(MaterialOptionFlag &lhs, const MaterialOptionFlag rhs);
}
