#pragma once

#include <exception>

namespace ObjectGL
{
	class RenderBufferException : public std::exception
	{
	public:
		RenderBufferException() = default;
		explicit RenderBufferException(char const* const _Message) noexcept;

		virtual ~RenderBufferException() = default;
	};
}