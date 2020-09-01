#pragma once

#include "UniformInterfaceHostCache.h"

namespace Danburite
{
	template <typename $DataType, size_t CACHE_SIZE>
	class UniformField
	{
	private:
		UniformInterfaceHostCache<CACHE_SIZE> &__cache;
		const size_t __offset;

	public:
		constexpr UniformField(UniformInterfaceHostCache<CACHE_SIZE> &cache, const size_t offset) noexcept;

		constexpr const $DataType &get() const noexcept;
		void set(const $DataType &data) const noexcept;

		virtual ~UniformField() = default;
	};

	template <typename $DataType, size_t ARRAY_SIZE, size_t CACHE_SIZE>
	class UniformFieldArray
	{
	private:
		UniformInterfaceHostCache<CACHE_SIZE>& __cache;
		const size_t __offset;

	public:
		constexpr UniformFieldArray(UniformInterfaceHostCache<CACHE_SIZE> &cache, const size_t offset) noexcept;

		constexpr const $DataType& get(const size_t idx) const noexcept;
		void set(const size_t idx, const $DataType &data) const noexcept;
		void set(const size_t idx, const size_t count, const $DataType *const pDataArr) const noexcept;

		virtual ~UniformFieldArray() = default;
	};

	template <typename $DataType, size_t CACHE_SIZE>
	constexpr UniformField<$DataType, CACHE_SIZE>::UniformField(
		UniformInterfaceHostCache<CACHE_SIZE> &cache, const size_t offset) noexcept :
		__cache { cache }, __offset { offset }
	{}

	template <typename $DataType, size_t CACHE_SIZE>
	constexpr const $DataType &UniformField<$DataType, CACHE_SIZE>::get() const noexcept
	{
		return __cache.get<$DataType>(__offset);
	}

	template <typename $DataType, size_t CACHE_SIZE>
	void UniformField<$DataType, CACHE_SIZE>::set(const $DataType &data) const noexcept
	{
		__cache.set(__offset, data);
	}

	template <typename $DataType, size_t ARRAY_SIZE, size_t CACHE_SIZE>
	constexpr UniformFieldArray<$DataType, ARRAY_SIZE, CACHE_SIZE>::
		UniformFieldArray(UniformInterfaceHostCache<CACHE_SIZE>& cache, const size_t offset) noexcept :
		__cache { cache }, __offset { offset }
	{}

	template <typename $DataType, size_t ARRAY_SIZE, size_t CACHE_SIZE>
	constexpr const $DataType &UniformFieldArray<$DataType, ARRAY_SIZE, CACHE_SIZE>::
		get(const size_t idx) const noexcept
	{
		return __cache.get<$DataType>(__offset + (sizeof($DataType) * idx));
	}

	template <typename $DataType, size_t ARRAY_SIZE, size_t CACHE_SIZE>
	void UniformFieldArray<$DataType, ARRAY_SIZE, CACHE_SIZE>::
		set(const size_t idx, const $DataType &data) const noexcept
	{
		__cache.set(__offset + (sizeof($DataType) * idx), data);
	}

	template <typename $DataType, size_t ARRAY_SIZE, size_t CACHE_SIZE>
	void UniformFieldArray<$DataType, ARRAY_SIZE, CACHE_SIZE>::
		set(const size_t idx, const size_t count, const $DataType *const pDataArr) const noexcept
	{
		__cache.set(__offset + (sizeof($DataType) * idx), count, pDataArr);
	}
}
