#pragma once

#include <exception>

namespace Danburite
{
	class AttachmentServerException : public std::exception
	{
	public:
		AttachmentServerException() = default;
		explicit AttachmentServerException(char const* const _Message) noexcept;

		virtual ~AttachmentServerException() = default;
	};
}