#include "VertexAttributeDescriptor.h"

namespace ObjectGL
{
	GLsizei VertexAttributeDescriptor::memSize() const noexcept
	{
		return (numElements * elementSize(elementType));
	}
}