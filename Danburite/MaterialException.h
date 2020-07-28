#pragma once

#include <exception>

namespace ObjectGL
{
	class MaterialException : public std::exception
	{
	public:
		MaterialException() = default;
		explicit MaterialException(char const* const _Message) noexcept;

		virtual ~MaterialException() = default;
	};
}