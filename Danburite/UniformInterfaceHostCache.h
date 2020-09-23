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
		void set(const size_t offset, const $DataType &data) noexcept;

		template <typename $DataType>
		void set(const size_t offset, const size_t count, const $DataType *const pDataArr) noexcept;

		constexpr const std::array<uint8_t, $BUFFER_SIZE> &getBuffer() const noexcept;

		constexpr bool isDirty() const noexcept;
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
	void UniformInterfaceHostCache<$BUFFER_SIZE>::set(const size_t offset, const $DataType &data) noexcept
	{
		constexpr size_t memSize = glm::max<size_t>(sizeof($DataType), 16ULL);

		void *const pTarget = (__buffer.data() + offset);
		const void *const pSrc = &data;
		if (!memcmp(pTarget, pSrc, memSize))
			return;

		auto &[dirtyMin, dirtyMax] = __dirtyRange;

		const size_t localDirtyMin = offset;
		const size_t localDirtyMax = (offset + memSize);

		dirtyMin = glm::min<size_t>(dirtyMin, localDirtyMin);
		dirtyMax = glm::max<size_t>(dirtyMax, localDirtyMax);

		memcpy(pTarget, pSrc, memSize);
	}

	template <size_t $BUFFER_SIZE>
	template <typename $DataType>
	void UniformInterfaceHostCache<$BUFFER_SIZE>::set(
		const size_t offset, const size_t count, const $DataType *const pDataArr) noexcept
	{
		if constexpr (sizeof($DataType) < 16ULL)
		{
			constexpr size_t memStride = 16ULL;

			for (size_t countIter = 0ULL; countIter < count; countIter++)
				set(offset + (countIter * memStride), pDataArr[countIter]);
		}
		else
		{
			const size_t memSize = (count * sizeof($DataType));

			void *const pTarget = (__buffer.data() + offset);
			if (!memcmp(pTarget, pDataArr, memSize))
				return;

			auto& [dirtyMin, dirtyMax] = __dirtyRange;

			const size_t localDirtyMin = offset;
			const size_t localDirtyMax = (offset + memSize);

			dirtyMin = glm::min<size_t>(dirtyMin, localDirtyMin);
			dirtyMax = glm::max<size_t>(dirtyMax, localDirtyMax);

			memcpy(pTarget, pDataArr, memSize);
		}
	}

	template <size_t $BUFFER_SIZE>
	constexpr const std::array<uint8_t, $BUFFER_SIZE> &
		UniformInterfaceHostCache<$BUFFER_SIZE>::getBuffer() const noexcept
	{
		return __buffer;
	}

	template <size_t $BUFFER_SIZE>
	constexpr bool UniformInterfaceHostCache<$BUFFER_SIZE>::isDirty() const noexcept
	{
		return (__dirtyRange.first < __dirtyRange.second);
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