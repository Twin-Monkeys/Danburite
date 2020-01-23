#pragma once

#include <exception>

namespace ObjectGL
{
	class RCException : public std::exception
	{
	public:
		RCException() = default;
		explicit RCException(char const* const _Message) noexcept;

		virtual ~RCException() = default;
	};
}