#pragma once

#include "BindableObject.h"
#include "BufferType.h"
#include "BufferUpdatePatternType.h"
#include <vector>
#include "BufferException.h"
#include "AssertException.h"
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
		Buffer(Buffer &&src) noexcept;

		void enableZeroInit(const bool enabled) noexcept;

		void memoryAlloc(const void *const pData, const GLsizeiptr size, const BufferUpdatePatternType updatePattern) noexcept;

		template <typename T, GLsizeiptr arrSize>
		void memoryAlloc(const T (&data)[arrSize], const BufferUpdatePatternType updatePattern) noexcept;

		template <typename T>
		void memoryAlloc(const std::initializer_list<T> &data, const BufferUpdatePatternType updatePattern) noexcept;

		template <typename T>
		void memoryAlloc(const std::vector<T> &data, const BufferUpdatePatternType updatePattern) noexcept;

		void memoryAlloc(const GLsizeiptr size, const BufferUpdatePatternType updatePattern) noexcept;

		void memoryCopy(const void *const pData, const GLintptr offset, const GLsizeiptr size) noexcept;
		void memoryFree() noexcept;
		void memorySet(const uint8_t value) noexcept;

		bool isMemoryAllocated() const noexcept;
		GLsizeiptr getMemorySize() const noexcept;

		void *mapHostInterface(const BufferAccessType accessType) noexcept;
		void unmapHostInterface() noexcept;

		Buffer &operator=(const Buffer &src) noexcept;

		virtual ~Buffer() noexcept;
	};

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
}
