#pragma once

#include <exception>

namespace Danburite
{
	class AssetImporterException : public std::exception
	{
	public:
		AssetImporterException() = default;
		explicit AssetImporterException(char const* const _Message) noexcept;

		virtual ~AssetImporterException() = default;
	};
}