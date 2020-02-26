#pragma once

#include "BindableObject.h"
#include "BufferType.h"
#include "BufferUpdatePatternType.h"
#include <vector>
#include "BufferException.h"
#include "BufferAccessType.h"

namespace ObjectGL
{
	class Buffer abstract : public BindableObject<Buffer, GLuint>
	{
	private:
		bool __memAllocated = false;
		GLsizeiptr __memSize = 0;

		bool __moved = false;
		bool __zeroInit = false;

		void __release() noexcept;

		static GLuint __createBufObj();

	protected:
		const GLenum __RAW_TYPE;

		Buffer(const BufferType type);

		virtual void _onBind() noexcept override;

	public:
		Buffer(const Buffer &src);
		constexpr Buffer(Buffer &&src) noexcept;

		constexpr void enableZeroInit(const bool enabled) noexcept;

		void memoryAlloc(const void *const pData, const GLsizeiptr size, const BufferUpdatePatternType updatePattern) noexcept;

		template <typename T, GLsizeiptr arrSize>
		void memoryAlloc(const T (&data)[arrSize], const BufferUpdatePatternType updatePattern) noexcept;

		template <typename T>
		void memoryAlloc(const std::initializer_list<T> &data, const BufferUpdatePatternType updatePattern) noexcept;

		template <typename T>
		void memoryAlloc(const std::vector<T> &data, const BufferUpdatePatternType updatePattern) noexcept;

		void memoryAlloc(const GLsizeiptr size, const BufferUpdatePatternType updatePattern) noexcept;

		void memoryCopy(const void *const pData, const GLsizeiptr size, const GLintptr offset = 0LL) noexcept;
		void memoryFree() noexcept;
		void memorySet(const uint8_t value) noexcept;

		constexpr bool isMemoryAllocated() const noexcept;
		constexpr GLsizeiptr getMemorySize() const noexcept;

		void *mapHostInterface(const BufferAccessType accessType) noexcept;
		void unmapHostInterface() noexcept;

		Buffer &operator=(const Buffer &src) noexcept;

		virtual ~Buffer() noexcept;
	};

	constexpr Buffer::Buffer(Buffer &&src) noexcept :
		BindableObject(src.ID), __RAW_TYPE(src.__RAW_TYPE)
	{
		src.__moved = true;
		__memAllocated = src.__memAllocated;
		__memSize = src.__memSize;
		__zeroInit = src.__zeroInit;
	}

	constexpr void Buffer::enableZeroInit(const bool enabled) noexcept
	{
		__zeroInit = enabled;
	}

	template <typename T, GLsizeiptr arrSize>
	void Buffer::memoryAlloc(const T(&data)[arrSize], const BufferUpdatePatternType updatePattern) noexcept
	{
		memoryAlloc(data, sizeof(T) * arrSize, updatePattern);
	}

	template <typename T>
	void Buffer::memoryAlloc(const std::initializer_list<T>& data, const BufferUpdatePatternType updatePattern) noexcept
	{
		memoryAlloc(data.begin(), sizeof(T) * data.size(), updatePattern);
	}

	template <typename T>
	void Buffer::memoryAlloc(const std::vector<T> &data, const BufferUpdatePatternType updatePattern) noexcept
	{
		memoryAlloc(data.data(), sizeof(T) * data.size(), updatePattern);
	}

	constexpr bool Buffer::isMemoryAllocated() const noexcept
	{
		return __memAllocated;
	}

	constexpr GLsizeiptr Buffer::getMemorySize() const noexcept
	{
		return __memSize;
	}
}
