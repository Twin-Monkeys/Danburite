#pragma once

#include <cstdint>

namespace Danburite
{
#pragma pack(push, 1)
	template <typename $DataType, size_t PADDING_SIZE = sizeof($DataType)>
	class PaddingField
	{
		static_assert(
			PADDING_SIZE >= sizeof($DataType),
			"Padding size must be equal to or greater than sizeof($DataType).");

	private:
		union
		{
			$DataType data {};
			std::uint8_t placeholder[PADDING_SIZE];
		}
		__buffer;

	public:
		PaddingField() = default;
		PaddingField(const $DataType &source);
		PaddingField($DataType &&source) noexcept;

		PaddingField &operator=(const $DataType &source);
		PaddingField &operator=($DataType &&source) noexcept;

		constexpr $DataType &operator*() noexcept;
		constexpr const $DataType &operator*() const noexcept;

		constexpr $DataType &operator->() noexcept;
		constexpr const $DataType &operator->() const noexcept;

		virtual ~PaddingField() = default;
	};
#pragma pack(pop)

	template <typename $DataType, size_t PADDING_SIZE>
	PaddingField<$DataType, PADDING_SIZE>::PaddingField(const $DataType &source) :
		__buffer { source }
	{}

	template <typename $DataType, size_t PADDING_SIZE>
	PaddingField<$DataType, PADDING_SIZE>::PaddingField($DataType &&source) noexcept :
		__buffer { std::move(source) }
	{}

	template <typename $DataType, size_t PADDING_SIZE>
	PaddingField<$DataType, PADDING_SIZE> &PaddingField<$DataType, PADDING_SIZE>::operator=(const $DataType& source)
	{
		__buffer.data = source;
	}

	template <typename $DataType, size_t PADDING_SIZE>
	PaddingField<$DataType, PADDING_SIZE> &PaddingField<$DataType, PADDING_SIZE>::operator=($DataType&& source) noexcept
	{
		__buffer.data = move(source);
	}

	template <typename $DataType, size_t PADDING_SIZE>
	constexpr $DataType &PaddingField<$DataType, PADDING_SIZE>::operator*() noexcept
	{
		return __buffer.data;
	}

	template <typename $DataType, size_t PADDING_SIZE>
	constexpr const $DataType &PaddingField<$DataType, PADDING_SIZE>::operator*() const noexcept
	{
		return __buffer.data;
	}

	template <typename $DataType, size_t PADDING_SIZE>
	constexpr $DataType &PaddingField<$DataType, PADDING_SIZE>::operator->() noexcept
	{
		return __buffer.data;
	}

	template <typename $DataType, size_t PADDING_SIZE>
	constexpr const $DataType &PaddingField<$DataType, PADDING_SIZE>::operator->() const noexcept
	{
		return __buffer.data;
	}
}