#pragma once

#include "UniformBuffer.h"
#include "UniformInterface.h"

namespace Danburite
{
	template <typename $UniformInterfaceType>
	class DeferredUniformBuffer
	{
		static_assert(
			std::is_base_of_v<UniformInterface<$UniformInterfaceType::BUFFER_SIZE>, $UniformInterfaceType>,
			"The type parameter must be derived from UniformInterface or its compatible types.");

	private:
		$UniformInterfaceType __interfaceInstance;
		ObjectGL::UniformBuffer __uniformBuffer;

	public:
		DeferredUniformBuffer(const bool memAlloc = true);

		constexpr $UniformInterfaceType &getInterface() noexcept;
		constexpr const $UniformInterfaceType &getInterface() const noexcept;

		constexpr operator ObjectGL::UniformBuffer &() noexcept;
		constexpr operator const ObjectGL::UniformBuffer &() const noexcept;

		void selfDeploy() noexcept;

		virtual ~DeferredUniformBuffer() = default;
	};

	template <typename $UniformInterfaceType>
	DeferredUniformBuffer<$UniformInterfaceType>::DeferredUniformBuffer(const bool memAlloc) :
		__uniformBuffer { __interfaceInstance.getBindingPoint() }
	{
		if (memAlloc)
			__uniformBuffer.memoryAlloc($UniformInterfaceType::BUFFER_SIZE, ObjectGL::BufferUpdatePatternType::STREAM);
	}

	template <typename $UniformInterfaceType>
	constexpr $UniformInterfaceType &DeferredUniformBuffer<$UniformInterfaceType>::getInterface() noexcept
	{
		return __interfaceInstance;
	}

	template <typename $UniformInterfaceType>
	constexpr const $UniformInterfaceType &
		DeferredUniformBuffer<$UniformInterfaceType>::getInterface() const noexcept
	{
		return __interfaceInstance;
	}

	template <typename $UniformInterfaceType>
	constexpr DeferredUniformBuffer<$UniformInterfaceType>::operator ObjectGL::UniformBuffer &() noexcept
	{
		return __uniformBuffer;
	}

	template <typename $UniformInterfaceType>
	constexpr DeferredUniformBuffer<$UniformInterfaceType>::operator const ObjectGL::UniformBuffer &() const noexcept
	{
		return __uniformBuffer;
	}

	template <typename $UniformInterfaceType>
	void DeferredUniformBuffer<$UniformInterfaceType>::selfDeploy() noexcept
	{
		UniformInterfaceHostCache<$UniformInterfaceType::BUFFER_SIZE> &cache = __interfaceInstance.getCache();

		const std::array<uint8_t, $UniformInterfaceType::BUFFER_SIZE> &buffer = cache.getBuffer();
		const auto &[dirtyMin, dirtyMax] = cache.getDirtyRange();

		if (dirtyMin >= dirtyMax)
			return;

		__uniformBuffer.memoryCopy(buffer.data() + dirtyMin, GLsizeiptr(dirtyMax - dirtyMin), dirtyMin);
		cache.clearDirty();
	}
}
