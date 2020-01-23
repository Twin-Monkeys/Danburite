#pragma once
#include "VertexAttributeFlag.h"

namespace Danburite
{
	enum class VertexAttributeType : unsigned
	{
		NONE							= 0U,
		POS3							= unsigned(VertexAttributeFlag::POS3),
		POS3_COLOR4						= unsigned(VertexAttributeFlag::POS3 | VertexAttributeFlag::COLOR4),
		POS3_NORMAL3					= unsigned(VertexAttributeFlag::POS3 | VertexAttributeFlag::NORMAL3),
		POS3_TEXCOORD2					= unsigned(VertexAttributeFlag::POS3 | VertexAttributeFlag::TEXCOORD2),
		POS3_COLOR4_NORMAL3				= unsigned(VertexAttributeFlag::POS3 | VertexAttributeFlag::COLOR4 | VertexAttributeFlag::NORMAL3),
		POS3_COLOR4_TEXCOORD2			= unsigned(VertexAttributeFlag::POS3 | VertexAttributeFlag::COLOR4 | VertexAttributeFlag::TEXCOORD2),
		POS3_NORMAL3_TEXCOORD2			= unsigned(VertexAttributeFlag::POS3 | VertexAttributeFlag::NORMAL3 | VertexAttributeFlag::TEXCOORD2),
		POS3_COLOR4_NORMAL3_TEXCOORD2	= unsigned(VertexAttributeFlag::POS3 | VertexAttributeFlag::COLOR4 | VertexAttributeFlag::NORMAL3 | VertexAttributeFlag::TEXCOORD2),

		MODELMAT16						= unsigned(VertexAttributeFlag::MODELMAT16)
	};

	constexpr bool operator&(const VertexAttributeType lhs, const VertexAttributeFlag rhs)
	{
		return (unsigned(lhs) & unsigned(rhs));
	}

	VertexAttributeType &operator|=(VertexAttributeType &lhs, const VertexAttributeFlag rhs);
}