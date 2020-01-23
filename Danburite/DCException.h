#pragma once

#include <exception>

namespace ObjectGL
{
	class DCException : public std::exception
	{
	public:
		DCException() = default;
		explicit DCException(char const* const _Message) noexcept;

		virtual ~DCException() = default;
	};
}