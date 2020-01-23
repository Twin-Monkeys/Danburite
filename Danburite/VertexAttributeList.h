#pragma once

#include "VertexAttribute.h"
#include <vector>

namespace ObjectGL
{
	class VertexAttributeList
	{
	private:
		std::vector<VertexAttribute> __entries;

	public:
		VertexAttributeList() = default;
		VertexAttributeList(const std::vector<VertexAttribute>& entries) noexcept;

		void add(
			const GLuint location, const GLint numElements, const ElementType elementType,
			const GLsizei stride, const GLsizei offset, const GLuint divisor = 0, const bool normalized = false) noexcept;

		void add(
			const GLuint location, const VertexAttributeDescriptor& desc,
			const GLsizei stride, const GLsizei offset, const GLuint divisor = 0) noexcept;

		void add(const VertexAttribute& attribute) noexcept;
		void add(const VertexAttributeList& attributeList) noexcept;

		void clear() noexcept;

		const std::vector<VertexAttribute>& getEntries() const noexcept;

		VertexAttribute& operator[](const size_t index) noexcept;
		const VertexAttribute& operator[](const size_t index) const noexcept;

		virtual ~VertexAttributeList() = default;
	};
}