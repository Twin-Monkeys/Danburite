#pragma once

#include <exception>

namespace Danburite
{
	class AnimationException : public std::exception
	{
	public:
		AnimationException() = default;
		explicit AnimationException(char const* const _Message) noexcept;

		virtual ~AnimationException() = default;
	};
}