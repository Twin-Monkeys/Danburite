#pragma once

namespace Danburite
{
	enum class VertexAttributeFlag : unsigned
	{
		NONE		= 0U,

		POS			= 0b0000'0000'0000'0001U,
		COLOR		= 0b0000'0000'0000'0010U,
		NORMAL		= 0b0000'0000'0000'0100U,
		TEXCOORD	= 0b0000'0000'0000'1000U,
		TANGENT		= 0b0000'0000'0001'0000U,
		BONE		= 0b0000'0000'0010'0000U,

		MODELMAT	= 0b0000'0000'0100'0000U
	};

	constexpr VertexAttributeFlag operator|(const VertexAttributeFlag lhs, const VertexAttributeFlag rhs)
	{
		return VertexAttributeFlag(unsigned(lhs) | unsigned(rhs));
	}

	constexpr bool operator&(const VertexAttributeFlag lhs, const VertexAttributeFlag rhs)
	{
		return (unsigned(lhs) & unsigned(rhs));
	}

	constexpr VertexAttributeFlag &operator|=(VertexAttributeFlag &lhs, const VertexAttributeFlag rhs)
	{
		lhs = VertexAttributeFlag(unsigned(lhs) | unsigned(rhs));
		return lhs;
	}
}
