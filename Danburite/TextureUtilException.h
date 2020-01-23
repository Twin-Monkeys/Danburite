#pragma once

#include <exception>

namespace Danburite
{
	class TextureUtilException : public std::exception
	{
	public:
		TextureUtilException() = default;
		explicit TextureUtilException(char const* const _Message) noexcept;

		virtual ~TextureUtilException() = default;
	};
}