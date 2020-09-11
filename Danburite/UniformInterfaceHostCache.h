#pragma once

#include <array>
#include <cstdint>
#include <glm/glm.hpp>

namespace Danburite
{
	template <size_t $BUFFER_SIZE>
	class UniformInterfaceHostCache
	{
	private:
		std::pair<size_t, size_t> __dirtyRange = { 0, $BUFFER_SIZE };
		std::array<uint8_t, $BUFFER_SIZE> __buffer { 0 };

	public:
		template <typename $DataType>
		constexpr const $DataType &get(const size_t offset) noexcept;

		template <typename $DataType>
		constexpr void set(const size_t offset, const $DataType &data) noexcept;

		template <typename $DataType>
		constexpr void set(const size_t offset, const size_t count, const $DataType *const pDataArr) noexcept;

		constexpr const std::array<uint8_t, $BUFFER_SIZE> &getBuffer() const noexcept;
		constexpr const std::pair<size_t, size_t> &getDirtyRange() const noexcept;
		constexpr void clearDirty() noexcept;
	};

	template <size_t $BUFFER_SIZE>
	template <typename $DataType>
	constexpr const $DataType &UniformInterfaceHostCache<$BUFFER_SIZE>::get(const size_t offset) noexcept
	{
		return *reinterpret_cast<$DataType*>(__buffer.data() + offset);
	}

	template <size_t $BUFFER_SIZE>
	template <typename $DataType>
	constexpr void UniformInterfaceHostCache<$BUFFER_SIZE>::set(const size_t offset, const $DataType &data) noexcept
	{
		auto &[dirtyMin, dirtyMax] = __dirtyRange;

		const size_t localDirtyMin = offset;
		const size_t localDirtyMax = (offset + sizeof($DataType));

		dirtyMin = glm::min<size_t>(dirtyMin, localDirtyMin);
		dirtyMax = glm::max<size_t>(dirtyMax, localDirtyMax);

		$DataType &target = *reinterpret_cast<$DataType *>(__buffer.data() + offset);
		target = data;
	}

	template <size_t $BUFFER_SIZE>
	template <typename $DataType>
	constexpr void UniformInterfaceHostCache<$BUFFER_SIZE>::set(
		const size_t offset, const size_t count, const $DataType *const pDataArr) noexcept
	{
		constexpr size_t memStride = glm::max<size_t>(sizeof($DataType), 16ULL);

		for (size_t countIter = 0ULL; countIter < count; countIter++)
			set(offset + (countIter * memStride), pDataArr[countIter]);
	}

	template <size_t $BUFFER_SIZE>
	constexpr const std::array<uint8_t, $BUFFER_SIZE> &
		UniformInterfaceHostCache<$BUFFER_SIZE>::getBuffer() const noexcept
	{
		return __buffer;
	}

	template <size_t $BUFFER_SIZE>
	constexpr const std::pair<size_t, size_t> &
		UniformInterfaceHostCache<$BUFFER_SIZE>::getDirtyRange() const noexcept
	{
		return __dirtyRange;
	}

	template <size_t $BUFFER_SIZE>
	constexpr void UniformInterfaceHostCache<$BUFFER_SIZE>::clearDirty() noexcept
	{
		__dirtyRange = { $BUFFER_SIZE, 0 };
	}
}