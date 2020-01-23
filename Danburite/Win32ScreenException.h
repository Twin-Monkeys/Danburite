#pragma once

#include <exception>

namespace Danburite
{
	class Win32ScreenException : public std::exception
	{
	public:
		Win32ScreenException() = default;
		explicit Win32ScreenException(char const* const _Message) noexcept;

		virtual ~Win32ScreenException() = default;
	};
}