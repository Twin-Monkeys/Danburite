#include "Buffer.h"
#include <algorithm>

using namespace std;

namespace ObjectGL
{
	GLuint Buffer::__createBufObj()
	{
		GLuint retVal;
		glGenBuffers(1, &retVal);

		if (!retVal)
			throw BufferException("Cannot create buffer");

		return retVal;
	}

	Buffer::Buffer(const BufferType type) :
		BindableObject(__createBufObj()), __RAW_TYPE(GLenum(type))
	{}

	Buffer::Buffer(const Buffer &src) :
		BindableObject(__createBufObj()), __RAW_TYPE(src.__RAW_TYPE)
	{
		*this = src;
	}

	Buffer::Buffer(Buffer &&src) noexcept :
		BindableObject(src.ID), __RAW_TYPE(src.__RAW_TYPE)
	{
		src.__moved = true;
		__memAllocated = src.__memAllocated;
		__memSize = src.__memSize;
	}

	void Buffer::__release() noexcept
	{
		if (!__moved)
			glDeleteBuffers(1, &ID);
	}

	void Buffer::_onBind() noexcept
	{
		glBindBuffer(__RAW_TYPE, ID);
	}

	void Buffer::enableZeroInit(const bool enabled) noexcept
	{
		__zeroInit = enabled;
	}

	void Buffer::memoryAlloc(const void *const pData, const GLsizeiptr size, const BufferUpdatePatternType updatePattern) noexcept
	{
		bind();
		glBufferData(__RAW_TYPE, size, pData, GLenum(updatePattern));

		__memAllocated = true;
		__memSize = size;
	}

	void Buffer::memoryCopy(const void *const pData, const GLintptr offset, const GLsizeiptr size) noexcept
	{
		AssertException::test(isMemoryAllocated());

		bind();
		glBufferSubData(__RAW_TYPE, offset, size, pData);
	}

	void Buffer::memoryAlloc(const GLsizeiptr size, const BufferUpdatePatternType updatePattern) noexcept
	{
		memoryAlloc(nullptr, size, updatePattern);

		if (__zeroInit)
			memorySet(0);
	}

	void Buffer::memoryFree() noexcept
	{
		bind();
		glBufferData(__RAW_TYPE, 0, nullptr, GL_STATIC_DRAW);

		__memAllocated = false;
		__memSize = 0;
	}

	void Buffer::memorySet(const uint8_t value) noexcept
	{
		AssertException::test(isMemoryAllocated());

		memset(mapHostInterface(BufferAccessType::WRITE_ONLY), 0, __memSize);
		unmapHostInterface();
	}

	bool Buffer::isMemoryAllocated() const noexcept
	{
		return __memAllocated;
	}

	GLsizeiptr Buffer::getMemorySize() const noexcept
	{
		return __memSize;
	}

	void *Buffer::mapHostInterface(const BufferAccessType accessType) noexcept
	{
		bind();
		return glMapBuffer(__RAW_TYPE, GLenum(accessType));
	}

	void Buffer::unmapHostInterface() noexcept
	{
		bind();
		glUnmapBuffer(__RAW_TYPE);
	}

	Buffer &Buffer::operator=(const Buffer &src) noexcept
	{
		if (src.isMemoryAllocated())
		{
			glBindBuffer(GL_COPY_READ_BUFFER, src.ID);
			glBindBuffer(GL_COPY_WRITE_BUFFER, ID);
			glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, src.__memSize);

			__memAllocated = true;
			__memSize = src.__memSize;
		}
		else
			memoryFree();

		return *this;
	}

	Buffer::~Buffer() noexcept
	{
		__release();
	}
}