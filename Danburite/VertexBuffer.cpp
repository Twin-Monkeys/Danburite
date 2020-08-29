#include "VertexBuffer.h"
#include <cassert>

using namespace std;

namespace ObjectGL
{
	VertexBuffer::VertexBuffer() :
		BufferBase(BufferType::VERTEX)
	{}

	void VertexBuffer::addAttribute(
		const GLuint location, const GLint numElements, const ElementType elementType,
		const GLsizei stride, const GLsizei offset, const GLuint divisor, const bool normalized) noexcept
	{
		__attribList.emplace_back(
			location,
			VertexAttributeDataStructure { numElements, elementType, normalized },
			stride, offset, divisor);
	}

	void VertexBuffer::addAttribute(
		const GLuint location, const VertexAttributeDataStructure &desc,
		const GLsizei stride, const GLsizei offset, const GLuint divisor) noexcept
	{
		__attribList.emplace_back(location, desc, stride, offset, divisor);
	}

	void VertexBuffer::addAttribute(const VertexAttribute &attribute) noexcept
	{
		__attribList.emplace_back(attribute);
	}

	void VertexBuffer::addAttributes(const vector<VertexAttribute> &attributeList) noexcept
	{
		__attribList.insert(__attribList.end(), attributeList.begin(), attributeList.end());
	}

	void VertexBuffer::setAttributes(const vector<VertexAttribute> &attributeList) noexcept
	{
		__attribList = attributeList;
	}

	void VertexBuffer::clearAttributes() noexcept
	{
		__attribList.clear();
	}

	void VertexBuffer::applyAttributes() noexcept
	{
		bind();
		for (const VertexAttribute &attribute : __attribList)
		{
			glVertexAttribPointer(
				attribute.location, attribute.desc.numElements,
				GLenum(attribute.desc.elementType), attribute.desc.normalized,
				attribute.stride, reinterpret_cast<const void *>(size_t(attribute.offset)));

			if (attribute.divisor)
				glVertexAttribDivisor(attribute.location, attribute.divisor);

			glEnableVertexAttribArray(attribute.location);
		}
	}
}