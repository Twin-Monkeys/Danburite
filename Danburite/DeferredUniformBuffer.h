#pragma once

#include "UniformBuffer.h"
#include "UniformInterface.h"

namespace Danburite
{
	template <typename $UniformInterfaceType, size_t BUFFER_SIZE>
	class DeferredUniformBuffer : public ObjectGL::UniformBuffer
	{
		static_assert(
			std::is_base_of_v<UniformInterface<BUFFER_SIZE>, $UniformInterfaceType>,
			"The type parameter must be derived from UniformInterface or its compatible types.");

	private:
		$UniformInterfaceType __interfaceInstance;

	public:
		DeferredUniformBuffer(const bool memAlloc = true);

		constexpr $UniformInterfaceType &getInterface() noexcept;
		constexpr const $UniformInterfaceType &getInterface() const noexcept;

		void selfDeploy() noexcept;

		virtual ~DeferredUniformBuffer() = default;
	};

	template <typename $UniformInterfaceType, size_t BUFFER_SIZE>
	DeferredUniformBuffer<$UniformInterfaceType, BUFFER_SIZE>::DeferredUniformBuffer(const bool memAlloc) :
		ObjectGL::UniformBuffer
		{
			__interfaceInstance.getBlockName(),
			__interfaceInstance.getBindingPoint()
		}
	{
		if (memAlloc)
			memoryAlloc(BUFFER_SIZE, BufferUpdatePatternType::STREAM);
	}

	template <typename $UniformInterfaceType, size_t BUFFER_SIZE>
	constexpr $UniformInterfaceType &
		DeferredUniformBuffer<$UniformInterfaceType, BUFFER_SIZE>::getInterface() noexcept
	{
		return __interfaceInstance;
	}

	template <typename $UniformInterfaceType, size_t BUFFER_SIZE>
	constexpr const $UniformInterfaceType &
		DeferredUniformBuffer<$UniformInterfaceType, BUFFER_SIZE>::getInterface() const noexcept
	{
		return __interfaceInstance;
	}

	template <typename $UniformInterfaceType, size_t BUFFER_SIZE>
	void DeferredUniformBuffer<$UniformInterfaceType, BUFFER_SIZE>::selfDeploy() noexcept
	{
		UniformInterfaceHostCache<BUFFER_SIZE> &cache = __interfaceInstance.getCache();
		const auto &[pStart, memSize] = cache.getDirtySpace();

		if (!pStart)
			return;

		memoryCopy(pStart, GLsizeiptr(memSize));
		cache.clearDirty();
	}
}
