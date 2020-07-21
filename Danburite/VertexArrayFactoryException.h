#pragma once

#include <exception>

namespace Danburite
{
	class VertexArrayFactoryException : public std::exception
	{
	public:
		VertexArrayFactoryException() = default;
		explicit VertexArrayFactoryException(char const* const _Message) noexcept;

		virtual ~VertexArrayFactoryException() = default;
	};
}