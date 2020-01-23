#pragma once

namespace Danburite
{
	enum class VertexAttributeFlag : unsigned
	{
		POS3		= 0b0000'0000'0000'0001U,
		COLOR4		= 0b0000'0000'0000'0010U,
		NORMAL3		= 0b0000'0000'0000'0100U,
		TEXCOORD2	= 0b0000'0000'0000'1000U,
		MODELMAT16	= 0b0000'0000'0001'0000U
	};

	constexpr VertexAttributeFlag operator|(const VertexAttributeFlag lhs, const VertexAttributeFlag rhs)
	{
		return VertexAttributeFlag(unsigned(lhs) | unsigned(rhs));
	}
}
