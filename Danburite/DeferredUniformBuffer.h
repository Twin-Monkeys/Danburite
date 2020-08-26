#pragma once

#include "UniformBuffer.h"
#include "UniformInterface.h"

namespace Danburite
{
	template <typename $UniformInterfaceType>
	class DeferredUniformBuffer : public ObjectGL::UniformBuffer
	{
		static_assert(
			std::is_base_of_v<UniformInterface, $UniformInterfaceType>,
			"The type parameter must be derived from UniformInterface or its compatible types.");

	private:
		$UniformInterfaceType __interfaceInstance;

	public:
		DeferredUniformBuffer(const std::string_view &blockName, const GLuint bindingPoint);

		constexpr $UniformInterfaceType &getInterface() noexcept;
		constexpr const $UniformInterfaceType &getInterface() const noexcept;

		void selfDeploy() noexcept;

		virtual ~DeferredUniformBuffer() = default;
	};

	template <typename $UniformInterfaceType>
	DeferredUniformBuffer<$UniformInterfaceType>::DeferredUniformBuffer(
		const std::string_view& blockName, const GLuint bindingPoint)
	{}

	template <typename $UniformInterfaceType>
	constexpr $UniformInterfaceType &DeferredUniformBuffer<$UniformInterfaceType>::getInterface() noexcept
	{
		return __interfaceInstance;
	}

	template <typename $UniformInterfaceType>
	constexpr const $UniformInterfaceType &DeferredUniformBuffer<$UniformInterfaceType>::getInterface() const noexcept
	{
		return __interfaceInstance;
	}

	template <typename $UniformInterfaceType>
	void DeferredUniformBuffer<$UniformInterfaceType>::selfDeploy() noexcept
	{
		const std::vector<uint8_t> &buffer = __interfaceInstance.getBuffer();
		memoryCopy(buffer.data(), buffer.size());
	}
}
