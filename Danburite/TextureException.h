#pragma once

#include <exception>

namespace ObjectGL
{
	class TextureException : public std::exception
	{
	public:
		TextureException() = default;
		explicit TextureException(char const* const _Message) noexcept;

		virtual ~TextureException() = default;
	};
}