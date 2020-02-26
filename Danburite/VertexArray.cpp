#pragma warning(disable: 4312 26451)

#include "VertexArray.h"
#include <cassert>

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
		assert(glGetError() == GL_NO_ERROR);
	}

	void VertexArray::__drawArrays(const GLsizei numInstances) noexcept
	{
		glDrawArraysInstanced(__primitiveType, __vertexStartingIndex, __numVertices, numInstances);
		assert(glGetError() == GL_NO_ERROR);
	}

	void VertexArray::__drawElements(const GLsizei numInstances) noexcept
	{
		glDrawElementsInstanced(
			__primitiveType, __numVertices, __IDX_TYPE,
			reinterpret_cast<const void *>(__vertexStartingIndex * __IDX_SIZE), numInstances);

		assert(glGetError() == GL_NO_ERROR);
	}

	void VertexArray::_onBind() noexcept
	{
		glBindVertexArray(ID);
		assert(glGetError() == GL_NO_ERROR);
	}

	void VertexArray::addVertexBuffer(const shared_ptr<VertexBuffer> &pVertexBuffer) noexcept
	{
		assert(pVertexBuffer);

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
		assert(glGetError() == GL_NO_ERROR);

		_unbind();
	}
}