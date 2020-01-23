#pragma once

#include <exception>

namespace ObjectGL
{
	class ProgramException : public std::exception
	{
	public:
		ProgramException() = default;
		explicit ProgramException(char const* const _Message) noexcept;

		virtual ~ProgramException() = default;
	};
}