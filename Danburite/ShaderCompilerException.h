#pragma once

#include <exception>

namespace ObjectGL
{
	class ShaderCompilerException : public std::exception
	{
	public:
		ShaderCompilerException() = default;
		explicit ShaderCompilerException(char const* const _Message) noexcept;

		virtual ~ShaderCompilerException() = default;
	};
}