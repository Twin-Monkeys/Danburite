#include "DeferredUniformBuffer.h"

using namespace std;

namespace Danburite
{
	DeferredUniformBuffer::DeferredUniformBuffer(const string_view &blockName, const GLuint bindingPoint) :
		UniformBuffer(blockName, bindingPoint)
	{}
}