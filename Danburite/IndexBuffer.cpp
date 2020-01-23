#include "IndexBuffer.h"

using namespace std;

namespace ObjectGL
{
	IndexBuffer::IndexBuffer(const IndexType indexType) :
		Buffer(BufferType::INDEX), __idxType(indexType)
	{}

	IndexType IndexBuffer::getIndexType() const noexcept
	{
		return __idxType;
	}

	void IndexBuffer::setIndexType(const IndexType type) noexcept
	{
		__idxType = type;
	}
}