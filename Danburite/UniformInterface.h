#pragma once

#include <string>
#include <GL/glew.h>
#include "UniformField.h"

namespace Danburite
{
	template <size_t $BUFFER_SIZE>
	class UniformInterface abstract
	{
	public:
		template <typename $DataType>
		using SpecializedUniformField = UniformField<$DataType, $BUFFER_SIZE>;

		template <typename $DataType, size_t ARRAY_SIZE>
		using SpecializedUniformFieldArray = UniformFieldArray<$DataType, ARRAY_SIZE, $BUFFER_SIZE>;

	private:
		const std::string __blockName;
		const GLuint __bindingPoint;

		UniformInterfaceHostCache<$BUFFER_SIZE> __cache;

	protected:
		template <typename $DataType>
		constexpr SpecializedUniformField<$DataType> _createField(const size_t offset) noexcept;

		template <typename $DataType, size_t ARRAY_SIZE>
		constexpr SpecializedUniformFieldArray<$DataType, ARRAY_SIZE> _createFieldArray(const size_t offset) noexcept;

	public:
		static constexpr size_t BUFFER_SIZE = $BUFFER_SIZE;

		UniformInterface(const std::string_view &blockName, const GLuint bindingPoint) noexcept;

		constexpr const std::string &getBlockName() const noexcept;
		constexpr GLuint getBindingPoint() const noexcept;

		constexpr UniformInterfaceHostCache<$BUFFER_SIZE>& getCache() noexcept;
		constexpr const UniformInterfaceHostCache<$BUFFER_SIZE> &getCache() const noexcept;

		virtual ~UniformInterface() = default;
	};

	template <size_t $BUFFER_SIZE>
	UniformInterface<$BUFFER_SIZE>::UniformInterface(
		const std::string_view& blockName, const GLuint bindingPoint) noexcept :
		__blockName { blockName }, __bindingPoint { bindingPoint }
	{}

	template <size_t $BUFFER_SIZE>
	template <typename $DataType>
	constexpr UniformInterface<$BUFFER_SIZE>::SpecializedUniformField<$DataType>
		UniformInterface<$BUFFER_SIZE>::_createField(const size_t offset) noexcept
	{
		return { __cache, offset };
	}

	template <size_t $BUFFER_SIZE>
	template <typename $DataType, size_t ARRAY_SIZE>
	constexpr UniformInterface<$BUFFER_SIZE>::SpecializedUniformFieldArray<$DataType, ARRAY_SIZE>
		UniformInterface<$BUFFER_SIZE>::_createFieldArray(const size_t offset) noexcept
	{
		return { __cache, offset };
	}

	template <size_t $BUFFER_SIZE>
	constexpr const std::string &UniformInterface<$BUFFER_SIZE>::getBlockName() const noexcept
	{
		return __blockName;
	}

	template <size_t $BUFFER_SIZE>
	constexpr GLuint UniformInterface<$BUFFER_SIZE>::getBindingPoint() const noexcept
	{
		return __bindingPoint;
	}

	template <size_t $BUFFER_SIZE>
	constexpr UniformInterfaceHostCache<$BUFFER_SIZE> &UniformInterface<$BUFFER_SIZE>::getCache() noexcept
	{
		return __cache;
	}

	template <size_t $BUFFER_SIZE>
	constexpr const UniformInterfaceHostCache<$BUFFER_SIZE> &UniformInterface<$BUFFER_SIZE>::getCache() const noexcept
	{
		return __cache;
	}
}
