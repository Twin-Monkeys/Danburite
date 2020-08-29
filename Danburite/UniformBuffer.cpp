#include "UniformBuffer.h"

using namespace std;

namespace ObjectGL
{
	UniformBuffer::UniformBuffer(const string_view &blockName, const GLuint bindingPoint) :
		BufferBase(BufferType::UNIFORM), __blockName(blockName), __bindingPoint(bindingPoint)
	{
		glBindBufferBase(__RAW_TYPE, __bindingPoint, ID);
	}
}