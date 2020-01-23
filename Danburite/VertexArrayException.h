#pragma once

#include <exception>

namespace ObjectGL
{
	class VertexArrayException : public std::exception
	{
	public:
		VertexArrayException() = default;
		explicit VertexArrayException(char const* const _Message) noexcept;

		virtual ~VertexArrayException() = default;
	};
}