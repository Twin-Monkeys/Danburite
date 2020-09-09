#include "UniformBuffer.h"

using namespace std;

namespace ObjectGL
{
	UniformBuffer::UniformBuffer(const GLuint bindingPoint) :
		BufferBase(BufferType::UNIFORM), __bindingPoint(bindingPoint)
	{
		glBindBufferBase(__RAW_TYPE, __bindingPoint, ID);
	}
}