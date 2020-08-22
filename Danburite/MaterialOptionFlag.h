#pragma once

#include <gl/glew.h>

namespace Danburite
{
	enum class MaterialOptionFlag : GLuint
	{
		NONE				= 0U,

		LIGHTING			= 0b0000'0000'0000'0001U,
		TRANSLUCENCY		= 0b0000'0000'0000'0010U,
		AMBIENT_TEXTURE		= 0b0000'0000'0000'0100U,
		DIFFUSE_TEXTURE		= 0b0000'0000'0000'1000U,

		SPECULAR_TEXTURE	= 0b0000'0000'0001'0000U,
		EMISSIVE_TEXTURE	= 0b0000'0000'0010'0000U,
		SHININESS_TEXTURE	= 0b0000'0000'0100'0000U,
		ALPHA_TEXTURE		= 0b0000'0000'1000'0000U,

		NORMAL_TEXTURE		= 0b0000'0001'0000'0000U,
		HEIGHT_TEXTURE		= 0b0000'0010'0000'0000U,

		ALPHA_OVERRIDING		= 0b0000'0100'0000'0000U
	};

	constexpr MaterialOptionFlag operator|(const MaterialOptionFlag lhs, const MaterialOptionFlag rhs)
	{
		return MaterialOptionFlag(GLuint(lhs) | GLuint(rhs));
	}

	constexpr bool operator&(const MaterialOptionFlag lhs, const MaterialOptionFlag rhs)
	{
		return (GLuint(lhs) & GLuint(rhs));
	}

	constexpr MaterialOptionFlag operator~(const MaterialOptionFlag flag) noexcept
	{
		return MaterialOptionFlag(~GLuint(flag));
	}

	constexpr MaterialOptionFlag &operator|=(MaterialOptionFlag &lhs, const MaterialOptionFlag rhs)
	{
		lhs = MaterialOptionFlag(GLuint(lhs) | GLuint(rhs));
		return lhs;
	}

	constexpr MaterialOptionFlag &operator&=(MaterialOptionFlag &lhs, const MaterialOptionFlag rhs)
	{
		lhs = MaterialOptionFlag(GLuint(lhs) & GLuint(rhs));
		return lhs;
	}
}
