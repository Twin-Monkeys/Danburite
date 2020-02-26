#pragma once

#include "Buffer.h"
#include "VertexAttributeList.h"
#include <memory>

namespace ObjectGL
{
	class VertexBuffer : public Buffer
	{
	private:
		VertexAttributeList __attribList;

	public:
		VertexBuffer();

		void addAttribute(
			const GLuint location, const GLint numElements, const ElementType elementType,
			const GLsizei stride, const GLsizei offset, const GLuint divisor = 0, const bool normalized = false) noexcept;

		void addAttribute(
			const GLuint location, const VertexAttributeDescriptor &desc,
			const GLsizei stride, const GLsizei offset, const GLuint divisor = 0) noexcept;

		void addAttribute(const VertexAttribute &attribute) noexcept;
		void addAttributes(const VertexAttributeList &attributeList) noexcept;
		void setAttributes(const VertexAttributeList &attributeList) noexcept;

		void clearAttributes() noexcept;
		void applyAttributes() noexcept;

		virtual ~VertexBuffer() = default;
	};
}
