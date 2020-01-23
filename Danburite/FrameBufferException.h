#pragma once

#include <exception>

namespace ObjectGL
{
	class FrameBufferException : public std::exception
	{
	public:
		FrameBufferException() = default;
		explicit FrameBufferException(char const* const _Message) noexcept;

		virtual ~FrameBufferException() = default;
	};
}