#pragma once

#include "UniformField.h"

namespace Danburite
{
	class UniformInterface abstract
	{
	private:
		std::vector<uint8_t> __buffer;

	protected:
		template <typename $DataType, size_t MEM_SIZE, typename ...$Args>
		UniformField<$DataType> _appendField($Args &&...args) noexcept;

	public:
		constexpr const std::vector<uint8_t> &getBuffer() const noexcept;
		virtual ~UniformInterface() = default;
	};

	template <typename $DataType, size_t MEM_SIZE, typename ...$Args>
	UniformField<$DataType> UniformInterface::_appendField($Args &&...args) noexcept
	{
		static_assert(
			MEM_SIZE >= sizeof($DataType),
			"MEM_SIZE must be bigger than or equal to sizeof($DataType).");

		const size_t offset = __buffer.size();
		__buffer.resize(offset + MEM_SIZE);

		new (__buffer.data() + offset) $DataType(std::forward<&Args>(args)...);
		return { __buffer, offset };
	}

	constexpr const std::vector<uint8_t> &UniformInterface::getBuffer() const noexcept
	{
		return __buffer;
	}
}
