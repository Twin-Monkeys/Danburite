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
		UniformBuffer(const std::string_view &blockName, const GLuint bindingPoint);

		constexpr const std::string& getBlockName() const noexcept;
		constexpr GLuint getBindingPoint() const noexcept;

		virtual ~UniformBuffer() = default;
	};

	constexpr const std::string &UniformBuffer::getBlockName() const noexcept
	{
		return __blockName;
	}

	constexpr GLuint UniformBuffer::getBindingPoint() const noexcept
	{
		return __bindingPoint;
	}
}