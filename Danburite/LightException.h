#pragma once

#include <exception>

namespace ObjectGL
{
	class LightException : public std::exception
	{
	public:
		LightException() = default;
		explicit LightException(char const* const _Message) noexcept;

		virtual ~LightException() = default;
	};
}