#pragma once

#include <string>

namespace ObjectGL
{
	class TextReader abstract
	{
	public:
		static std::string read(const std::string_view &path);
	};
}