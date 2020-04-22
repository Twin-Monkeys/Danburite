#pragma once

#include "ElementType.h"

namespace ObjectGL
{
	class VertexAttributeDataStructure
	{
	public:
		GLint numElements;
		ElementType elementType;
		bool normalized;

		constexpr VertexAttributeDataStructure(
			const GLint numElements, const ElementType elementType, const bool normalized = false) noexcept;

		constexpr GLsizei memSize() const noexcept;

		virtual ~VertexAttributeDataStructure() = default;
	};

	constexpr VertexAttributeDataStructure::VertexAttributeDataStructure(
		const GLint numElements, const ElementType elementType, const bool normalized) noexcept :
		numElements(numElements), elementType(elementType), normalized(normalized)
	{}

	constexpr GLsizei VertexAttributeDataStructure::memSize() const noexcept
	{
		return (numElements * elementSize(elementType));
	}
}