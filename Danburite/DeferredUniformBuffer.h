#pragma once

#include "UniformBuffer.h"

namespace Danburite
{
	template <typename $UniformInterfaceType>
	class DeferredUniformBuffer : public ObjectGL::UniformBuffer
	{
	public:
		DeferredUniformBuffer(const std::string_view &blockName, const GLuint bindingPoint);
		virtual ~DeferredUniformBuffer() = default;
	};
}
