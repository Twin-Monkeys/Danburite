#pragma once

#include <string>
#include "UniformField.h"

namespace Danburite
{
	class UniformInterface abstract
	{
	private:
		const std::string __blockName;
		const GLuint __bindingPoint;

		std::vector<uint8_t> __buffer;

	protected:
		template <typename $DataType, size_t MEM_SIZE = sizeof($DataType)>
		UniformField<$DataType> _appendField() noexcept;

	public:
		UniformInterface(const std::string_view &blockName, const GLuint bindingPoint) noexcept;

		constexpr const std::string &getBlockName() const noexcept;
		constexpr GLuint getBindingPoint() const noexcept;

		constexpr const std::vector<uint8_t> &getBuffer() const noexcept;
		virtual ~UniformInterface() = default;
	};

	UniformInterface::UniformInterface(
		const std::string_view& blockName, const GLuint bindingPoint) noexcept :
		__blockName { blockName }, __bindingPoint { bindingPoint }
	{}

	template <typename $DataType, size_t MEM_SIZE>
	UniformField<$DataType> UniformInterface::_appendField() noexcept
	{
		static_assert(
			MEM_SIZE >= sizeof($DataType),
			"MEM_SIZE must be bigger than or equal to sizeof($DataType).");

		const size_t offset = __buffer.size();
		__buffer.resize(offset + MEM_SIZE);

		return { __buffer, offset };
	}

	constexpr const std::string &UniformInterface::getBlockName() const noexcept
	{
		return __blockName;
	}

	constexpr GLuint UniformInterface::getBindingPoint() const noexcept
	{
		return __bindingPoint;
	}

	constexpr const std::vector<uint8_t> &UniformInterface::getBuffer() const noexcept
	{
		return __buffer;
	}
}
