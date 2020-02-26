#include "IndexBuffer.h"

using namespace std;

namespace ObjectGL
{
	IndexBuffer::IndexBuffer(const IndexType indexType) :
		Buffer(BufferType::INDEX), __idxType(indexType)
	{}
}