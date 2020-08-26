#pragma once

#include <vector>
#include <cstdint>

namespace Danburite
{
	template <typename $DataType>
	class UniformField
	{
	private:
		std::vector<uint8_t> &__bufferRef;
		const size_t __offset;

		$DataType *__getReference() const noexcept;

	public:
		constexpr UniformField(std::vector<uint8_t> &bufferReference, const size_t offset) noexcept;

		$DataType &operator*() const noexcept;
		$DataType *operator->() const noexcept;

		virtual ~UniformField() = default;
	};

	template <typename $DataType>
	$DataType *UniformField<$DataType>::__getReference() const noexcept
	{
		return reinterpret_cast<$DataType *>(__bufferRef.data() + __offset);
	}

	template <typename $DataType>
	constexpr UniformField<$DataType>::UniformField(
		std::vector<uint8_t> &bufferReference, const size_t offset) noexcept :
		__bufferRef(bufferReference), __offset(offset)
	{}

	template <typename $DataType>
	$DataType &UniformField<$DataType>::operator*() const noexcept
	{
		return *__getReference();
	}

	template <typename $DataType>
	$DataType *UniformField<$DataType>::operator->() const noexcept
	{
		return __getReference();
	}
}
