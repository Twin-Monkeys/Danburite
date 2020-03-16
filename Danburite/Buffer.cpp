#include "Buffer.h"
#include <algorithm>
#include <cassert>

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

	void Buffer::__release() noexcept
	{
		if (!__moved)
		{
			glDeleteBuffers(1, &ID);
		}
	}

	void Buffer::_onBind() noexcept
	{
		glBindBuffer(__RAW_TYPE, ID);
	}

	void Buffer::memoryAlloc(const void *const pData, const GLsizeiptr size, const BufferUpdatePatternType updatePattern) noexcept
	{
		bind();
		glBufferData(__RAW_TYPE, size, pData, GLenum(updatePattern));

		__memAllocated = true;
		__memSize = size;
	}

	void Buffer::memoryCopy(const void *const pData, const GLsizeiptr size, const GLintptr offset) noexcept
	{
		assert(isMemoryAllocated());

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
		assert(isMemoryAllocated());

		memset(mapHostInterface(BufferAccessType::WRITE_ONLY), 0, __memSize);
		unmapHostInterface();
	}

	void *Buffer::mapHostInterface(const BufferAccessType accessType) noexcept
	{
		bind();

		void *const pRetVal = glMapBuffer(__RAW_TYPE, GLenum(accessType));
	
		return pRetVal;
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