#pragma once

#include "BufferBase.h"

namespace ObjectGL
{
	class UniformBuffer : public BufferBase
	{
	private:
		const std::string __blockName;
		const GLuint __bindingPoint;

	public:
		explicit UniformBuffer(const GLuint bindingPoint);
		constexpr GLuint getBindingPoint() const noexcept;

		virtual ~UniformBuffer() = default;
	};

	constexpr GLuint UniformBuffer::getBindingPoint() const noexcept
	{
		return __bindingPoint;
	}
}