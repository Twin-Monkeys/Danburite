#include "IndexBuffer.h"

using namespace std;

namespace ObjectGL
{
	IndexBuffer::IndexBuffer(const IndexType indexType) :
		BufferBase(BufferType::INDEX), __idxType(indexType)
	{}
}