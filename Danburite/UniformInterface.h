#pragma once

#include <vector>
#include <cstdint>

namespace Danburite
{
	class UniformInterface
	{
	private:
		std::vector<uint8_t> __placeholder;

	public:
		virtual ~UniformInterface() = default;
	};
}
