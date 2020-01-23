#pragma warning(disable: 4312 26451)

#include "VertexArray.h"

using namespace std;

namespace ObjectGL
{
	GLuint VertexArray::__createVAO()
	{
		GLuint retVal;
		glGenVertexArrays(1, &retVal);

		if (!retVal)
			throw VertexArrayException("Cannot create vertex array");

		return retVal;
	}

	VertexArray::VertexArray(
		const shared_ptr<VertexBuffer> &pVertexBuffer,
		const GLsizei numVertices) :
		VertexArray(unordered_set<shared_ptr<VertexBuffer>> { pVertexBuffer }, numVertices)
	{}

	VertexArray::VertexArray(
		const unordered_set<shared_ptr<VertexBuffer>> &vertexBuffers,
		const GLsizei numVertices) :
		BindableObject(__createVAO()),
		__vertexBuffersHolder(vertexBuffers), __numVertices(numVertices),
		__pDrawFunc(&VertexArray::__drawArrays)
	{
		bind();

		for (const shared_ptr<VertexBuffer> &pVertexBuffer : vertexBuffers)
			pVertexBuffer->applyAttributes();

		unbind();
	}

	VertexArray::VertexArray(
		const shared_ptr<VertexBuffer> &pVertexBuffer,
		const shared_ptr<IndexBuffer> &pIndexBuffer,
		const GLsizei numVertices) :
		VertexArray(unordered_set<shared_ptr<VertexBuffer>> { pVertexBuffer }, pIndexBuffer, numVertices)
	{}

	VertexArray::VertexArray(
		const unordered_set<shared_ptr<VertexBuffer>> &vertexBuffers,
		const std::shared_ptr<IndexBuffer> &pIndexBuffer,
		const GLsizei numVertices) :
		BindableObject(__createVAO()),
		__vertexBuffersHolder(vertexBuffers), __pIndexBuffer(pIndexBuffer), __numVertices(numVertices),
		__IDX_TYPE(GLenum(pIndexBuffer->getIndexType())),
		__IDX_SIZE(indexSize(pIndexBuffer->getIndexType())),
		__pDrawFunc(&VertexArray::__drawElements)
	{
		bind();

		for (const shared_ptr<VertexBuffer> &pVertexBuffer : vertexBuffers)
			pVertexBuffer->applyAttributes();

		pIndexBuffer->bind();

		unbind();
	}

	void VertexArray::__release() noexcept
	{
		glDeleteVertexArrays(1, &ID);
	}

	void VertexArray::__drawArrays(const GLsizei numInstances) noexcept
	{
		glDrawArraysInstanced(__primitiveType, __vertexStartingIndex, __numVertices, numInstances);
	}

	void VertexArray::__drawElements(const GLsizei numInstances) noexcept
	{
		glDrawElementsInstanced(
			__primitiveType, __numVertices, __IDX_TYPE,
			reinterpret_cast<const void *>(__vertexStartingIndex * __IDX_SIZE), numInstances);
	}

	void VertexArray::_onBind() noexcept
	{
		glBindVertexArray(ID);
	}

	PrimitiveType VertexArray::getPrimitiveType() const noexcept
	{
		return PrimitiveType(__primitiveType);
	}

	GLint VertexArray::getVertexStartingIndex() const noexcept
	{
		return __vertexStartingIndex;
	}

	GLsizei VertexArray::getNumVertices() const noexcept
	{
		return __numVertices;
	}

	void VertexArray::setPrimitiveType(const PrimitiveType primitiveType) noexcept
	{
		__primitiveType = GLenum(primitiveType);
	}

	void VertexArray::setVertexStartingIndex(const GLint index) noexcept
	{
		__vertexStartingIndex = index;
	}

	void VertexArray::setNumVertices(const GLsizei numVertices) noexcept
	{
		__numVertices = numVertices;
	}

	void VertexArray::setDrawInfo(
		const PrimitiveType primitiveType, const GLint vertexStartingIndex, const GLsizei numVertices) noexcept
	{
		__primitiveType = GLenum(primitiveType);
		__vertexStartingIndex = vertexStartingIndex;
		__numVertices = numVertices;
	}

	void VertexArray::addVertexBuffer(const shared_ptr<VertexBuffer> &pVertexBuffer) noexcept
	{
		AssertException::test(pVertexBuffer);

		__vertexBuffersHolder.emplace(pVertexBuffer);

		bind();
		pVertexBuffer->applyAttributes();
		unbind();
	}

	void VertexArray::draw(const GLsizei numInstances) noexcept
	{
		bind();
		(this->*__pDrawFunc)(numInstances);
		unbind();
	}

	VertexArray::~VertexArray() noexcept
	{
		__release();
	}

	void VertexArray::unbind() noexcept
	{
		glBindVertexArray(0);
		_unbind();
	}
}