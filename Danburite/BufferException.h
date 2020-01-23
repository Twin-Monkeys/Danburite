#pragma once

#include <exception>

namespace ObjectGL
{
	class BufferException : public std::exception
	{
	public:
		BufferException() = default;
		explicit BufferException(char const* const _Message) noexcept;

		virtual ~BufferException() = default;
	};
}