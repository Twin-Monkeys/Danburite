#pragma once

#include "BufferBase.h"
#include "IndexType.h"

namespace ObjectGL
{
	class IndexBuffer : public BufferBase
	{
	private:
		IndexType __idxType;

	public:
		IndexBuffer(const IndexType indexType = IndexType::UNSIGNED_INT);

		constexpr IndexType getIndexType() const noexcept;
		constexpr void setIndexType(const IndexType type) noexcept;

		virtual ~IndexBuffer() = default;
	};

	constexpr IndexType IndexBuffer::getIndexType() const noexcept
	{
		return __idxType;
	}

	constexpr void IndexBuffer::setIndexType(const IndexType type) noexcept
	{
		__idxType = type;
	}
}