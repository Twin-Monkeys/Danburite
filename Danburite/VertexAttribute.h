#pragma once

#include "VertexAttributeDataStructure.h"
#include <string>

namespace ObjectGL
{
	class VertexAttribute
	{
	public:
		GLuint location;
		VertexAttributeDataStructure desc;
		GLsizei stride;
		GLsizei offset;
		GLuint divisor;

		VertexAttribute() = default;
		constexpr VertexAttribute(
			const GLuint location, const VertexAttributeDataStructure &desc,
			const GLsizei stride, const GLsizei offset, const GLuint divisor = 0) noexcept;

		virtual ~VertexAttribute() = default;
	};

	constexpr VertexAttribute::VertexAttribute(
		const GLuint location, const VertexAttributeDataStructure& desc,
		const GLsizei stride, const GLsizei offset, const GLuint divisor) noexcept :
		location(location), desc(desc), stride(stride), offset(offset), divisor(divisor)
	{}
}