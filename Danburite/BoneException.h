#pragma once

#include <exception>

namespace Danburite
{
	class BoneException : public std::exception
	{
	public:
		BoneException() = default;
		explicit BoneException(char const* const _Message) noexcept;

		virtual ~BoneException() = default;
	};
}