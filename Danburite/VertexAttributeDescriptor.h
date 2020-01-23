#pragma once

#include "ElementType.h"

namespace ObjectGL
{
	class VertexAttributeDescriptor
	{
	public:
		GLint numElements;
		ElementType elementType;
		bool normalized;

		constexpr VertexAttributeDescriptor(
			const GLint numElements, const ElementType elementType, const bool normalized = false) noexcept;

		constexpr GLsizei memSize() const noexcept;

		virtual ~VertexAttributeDescriptor() = default;
	};

	constexpr VertexAttributeDescriptor::VertexAttributeDescriptor(
		const GLint numElements, const ElementType elementType, const bool normalized) noexcept :
		numElements(numElements), elementType(elementType), normalized(normalized)
	{}

	constexpr GLsizei VertexAttributeDescriptor::memSize() const noexcept
	{
		return (numElements * elementSize(elementType));
	}
}