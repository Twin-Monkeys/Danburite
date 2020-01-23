#include "VertexBuffer.h"

using namespace std;

namespace ObjectGL
{
	VertexBuffer::VertexBuffer() :
		Buffer(BufferType::VERTEX)
	{}

	void VertexBuffer::addAttribute(
		const GLuint location, const GLint numElements, const ElementType elementType,
		const GLsizei stride, const GLsizei offset, const GLuint divisor, const bool normalized) noexcept
	{
		__attribList.add(location, numElements, elementType, stride, offset, divisor, normalized);
	}

	void VertexBuffer::addAttribute(
		const GLuint location, const VertexAttributeDescriptor &desc,
		const GLsizei stride, const GLsizei offset, const GLuint divisor) noexcept
	{
		__attribList.add(location, desc, stride, offset, divisor);
	}

	void VertexBuffer::addAttribute(const VertexAttribute &attribute) noexcept
	{
		__attribList.add(attribute);
	}

	void VertexBuffer::addAttributes(const VertexAttributeList &attributeList) noexcept
	{
		__attribList.add(attributeList);
	}

	void VertexBuffer::setAttributes(const VertexAttributeList &attributeList) noexcept
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
		for (const VertexAttribute &attribute : __attribList.getEntries())
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