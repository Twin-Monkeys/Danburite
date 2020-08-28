#pragma once

#include <array>
#include <cstdint>
#include <glm/glm.hpp>

namespace Danburite
{
	template <size_t BUFFER_SIZE>
	class DirtyFlaggedBuffer
	{
	private:
		bool __dirty = true;
		std::pair<size_t, size_t> __dirtyRange = { 0, BUFFER_SIZE };

		std::array<uint8_t, BUFFER_SIZE> __buffer { 0 };

	public:
		template <typename $DataType>
		constexpr void set(const size_t offset, const $DataType &data) noexcept;
	};

	template <size_t BUFFER_SIZE>
	template <typename $DataType>
	constexpr void DirtyFlaggedBuffer<BUFFER_SIZE>::set(const size_t offset, const $DataType& data) noexcept
	{
		auto &[dirtyMin, dirtyMax] = __dirtyRange;

		const size_t localDirtyMin = offset;
		const size_t localDirtyMax = (offset + sizeof($DataType));

		__dirty = true;
		dirtyMin = glm::min(dirtyMin, localDirtyMin);
		dirtyMax = glm::max(dirtyMax, localDirtyMax);

		$DataType &target = reinterpret_cast<$DataType *>(__buffer.data() + offset);
		target = data;
	}
}