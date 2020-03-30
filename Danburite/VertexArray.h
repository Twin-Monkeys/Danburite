#pragma once

#include "VertexBuffer.h"
#include "BindableObject.h"
#include <unordered_set>
#include "PrimitiveType.h"
#include "VertexArrayException.h"
#include "IndexBuffer.h"

namespace ObjectGL
{
	class VertexArray : public BindableObject<VertexArray, GLuint>
	{
	private:
		std::unordered_set<std::shared_ptr<VertexBuffer>> __vertexBuffersHolder;
		const std::shared_ptr<IndexBuffer> __pIndexBuffer;

		GLenum __primitiveType = GLenum(PrimitiveType::TRIANGLES);
		GLint __vertexStartingIndex = 0;
		GLsizei __numVertices;

		const GLenum __IDX_TYPE = 0;
		const GLint __IDX_SIZE = 0;

		void (VertexArray::*const __pDrawFunc)(const GLsizei) noexcept;

		VertexArray(const VertexArray &) = delete;
		VertexArray& operator=(const VertexArray &) = delete;

		void __release() noexcept;

		void __drawArrays(const GLsizei numInstances) noexcept;
		void __drawElements(const GLsizei numInstances) noexcept;

		static GLuint __createVAO();

	protected:
		virtual void _onBind() noexcept override;

	public:
		explicit VertexArray(const GLsizei numVertices);

		VertexArray(
			const std::shared_ptr<VertexBuffer> &pVertexBuffer,
			const GLsizei numVertices);

		VertexArray(
			const std::unordered_set<std::shared_ptr<VertexBuffer>> &vertexBuffers,
			const GLsizei numVertices);

		VertexArray(
			const std::shared_ptr<VertexBuffer> &pVertexBuffer,
			const std::shared_ptr<IndexBuffer> &pIndexBuffer,
			const GLsizei numVertices);

		VertexArray(
			const std::unordered_set<std::shared_ptr<VertexBuffer>> &vertexBuffers,
			const std::shared_ptr<IndexBuffer> &pIndexBuffer,
			const GLsizei numVertices);

		constexpr PrimitiveType getPrimitiveType() const noexcept;
		constexpr GLint getVertexStartingIndex() const noexcept;
		constexpr GLsizei getNumVertices() const noexcept;

		constexpr void setPrimitiveType(const PrimitiveType primitiveType) noexcept;
		constexpr void setVertexStartingIndex(const GLint index) noexcept;
		constexpr void setNumVertices(const GLsizei numVertices) noexcept;
		constexpr void setDrawInfo(const PrimitiveType primitiveType, const GLint vertexStartingIndex, const GLsizei numVertices) noexcept;

		void addVertexBuffer(const std::shared_ptr<VertexBuffer> &pVertexBuffer) noexcept;

		void draw(const GLsizei numInstances = 1) noexcept;

		virtual ~VertexArray() noexcept;

		static void unbind() noexcept;
	};

	constexpr PrimitiveType VertexArray::getPrimitiveType() const noexcept
	{
		return PrimitiveType(__primitiveType);
	}

	constexpr GLint VertexArray::getVertexStartingIndex() const noexcept
	{
		return __vertexStartingIndex;
	}

	constexpr GLsizei VertexArray::getNumVertices() const noexcept
	{
		return __numVertices;
	}

	constexpr void VertexArray::setPrimitiveType(const PrimitiveType primitiveType) noexcept
	{
		__primitiveType = GLenum(primitiveType);
	}

	constexpr void VertexArray::setVertexStartingIndex(const GLint index) noexcept
	{
		__vertexStartingIndex = index;
	}

	constexpr void VertexArray::setNumVertices(const GLsizei numVertices) noexcept
	{
		__numVertices = numVertices;
	}

	constexpr void VertexArray::setDrawInfo(
		const PrimitiveType primitiveType, const GLint vertexStartingIndex, const GLsizei numVertices) noexcept
	{
		setPrimitiveType(primitiveType);
		setVertexStartingIndex(vertexStartingIndex);
		setNumVertices(numVertices);
	}
}