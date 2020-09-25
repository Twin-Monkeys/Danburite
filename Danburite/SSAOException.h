#pragma once

#include <exception>

namespace Danburite
{
	class SSAOException : public std::exception
	{
	public:
		SSAOException() = default;
		explicit SSAOException(char const* const _Message) noexcept;

		virtual ~SSAOException() = default;
	};
}