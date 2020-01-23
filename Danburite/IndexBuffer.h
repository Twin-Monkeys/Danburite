#pragma once

#include "Buffer.h"
#include "IndexType.h"

namespace ObjectGL
{
	class IndexBuffer : public Buffer
	{
	private:
		IndexType __idxType;

	public:
		IndexBuffer(const IndexType indexType = IndexType::UNSIGNED_INT);

		IndexType getIndexType() const noexcept;
		void setIndexType(const IndexType type) noexcept;

		virtual ~IndexBuffer() = default;
	};
}