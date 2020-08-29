#pragma once

#include "BufferBase.h"
#include "VertexAttribute.h"
#include <memory>

namespace ObjectGL
{
	class VertexBuffer : public BufferBase
	{
	private:
		std::vector<VertexAttribute> __attribList;

	public:
		VertexBuffer();

		void addAttribute(
			const GLuint location, const GLint numElements, const ElementType elementType,
			const GLsizei stride, const GLsizei offset, const GLuint divisor = 0, const bool normalized = false) noexcept;

		void addAttribute(
			const GLuint location, const VertexAttributeDataStructure &desc,
			const GLsizei stride, const GLsizei offset, const GLuint divisor = 0) noexcept;

		void addAttribute(const VertexAttribute &attribute) noexcept;
		void addAttributes(const std::vector<VertexAttribute> &attributeList) noexcept;
		void setAttributes(const std::vector<VertexAttribute> &attributeList) noexcept;

		void clearAttributes() noexcept;
		void applyAttributes() noexcept;

		virtual ~VertexBuffer() = default;
	};
}
