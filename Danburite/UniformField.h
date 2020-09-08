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

		const UniformField &operator=(const $DataType &data) const noexcept;

		virtual ~UniformField() = default;
	};

	template <typename $DataType, size_t ARRAY_SIZE, size_t CACHE_SIZE>
	class UniformFieldArray
	{
	private:
		UniformInterfaceHostCache<CACHE_SIZE>& __cache;
		const size_t __offset;

	public:
		class IndexedReference
		{
		public:
			const size_t idx;
			const $DataType &data;

			constexpr IndexedReference(const size_t idx, const $DataType &data) noexcept;
		};

		class IndexedRangedReference
		{
		public:
			const size_t idx;
			const size_t count;
			const $DataType *const pDataArr;

			constexpr IndexedRangedReference(const size_t idx, const size_t count, const $DataType *const pDataArr) noexcept;
		};

		constexpr UniformFieldArray(UniformInterfaceHostCache<CACHE_SIZE> &cache, const size_t offset) noexcept;

		constexpr const $DataType& get(const size_t idx) const noexcept;
		void set(const size_t idx, const $DataType &data) const noexcept;
		void set(const size_t idx, const size_t count, const $DataType *const pDataArr) const noexcept;

		const UniformFieldArray &operator=(const IndexedReference &index_data) const noexcept;
		const UniformFieldArray &operator=(const IndexedRangedReference &index_count_pDataArr) const noexcept;

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

	template <typename $DataType, size_t CACHE_SIZE>
	const UniformField<$DataType, CACHE_SIZE> &UniformField<$DataType, CACHE_SIZE>::operator=(const $DataType &data) const noexcept
	{
		set(data);
		return *this;
	}

	template <typename $DataType, size_t ARRAY_SIZE, size_t CACHE_SIZE>
	constexpr UniformFieldArray<$DataType, ARRAY_SIZE, CACHE_SIZE>::
		IndexedReference::IndexedReference(const size_t idx, const $DataType &data) noexcept :
		idx { idx }, data { data }
	{}

	template <typename $DataType, size_t ARRAY_SIZE, size_t CACHE_SIZE>
	constexpr UniformFieldArray<$DataType, ARRAY_SIZE, CACHE_SIZE>::
		IndexedRangedReference::IndexedRangedReference(const size_t idx, const size_t count, const $DataType *const pDataArr) noexcept :
		idx { idx }, count { count }, pDataArr { pDataArr }
	{}

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

	template <typename $DataType, size_t ARRAY_SIZE, size_t CACHE_SIZE>
	const UniformFieldArray<$DataType, ARRAY_SIZE, CACHE_SIZE> &
		UniformFieldArray<$DataType, ARRAY_SIZE, CACHE_SIZE>::operator=(const IndexedReference &index_data) const noexcept
	{
		const auto &[index, data] = index_data;
		set(index, data);

		return *this;
	}

	template <typename $DataType, size_t ARRAY_SIZE, size_t CACHE_SIZE>
	const UniformFieldArray<$DataType, ARRAY_SIZE, CACHE_SIZE> &
		UniformFieldArray<$DataType, ARRAY_SIZE, CACHE_SIZE>::operator=(const IndexedRangedReference &index_count_pDataArr) const noexcept
	{
		const auto &[index, count, pDataArr] = index_count_pDataArr;
		set(index, count, pDataArr);

		return *this;
	}
}
