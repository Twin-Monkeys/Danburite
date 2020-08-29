#include "BufferBase.h"
#include <algorithm>
#include <cassert>

using namespace std;

namespace ObjectGL
{
	GLuint BufferBase::__createBufObj()
	{
		GLuint retVal;
		glGenBuffers(1, &retVal);

		if (!retVal)
			throw BufferException("Cannot create buffer");

		return retVal;
	}

	BufferBase::BufferBase(const BufferType type) :
		BindableObject(__createBufObj()), __RAW_TYPE(GLenum(type))
	{}

	BufferBase::BufferBase(const BufferBase &src) :
		BindableObject(__createBufObj()), __RAW_TYPE(src.__RAW_TYPE)
	{
		*this = src;
	}

	void BufferBase::__release() noexcept
	{
		if (!__moved)
		{
			glDeleteBuffers(1, &ID);
		}
	}

	void BufferBase::_onBind() noexcept
	{
		glBindBuffer(__RAW_TYPE, ID);
	}

	void BufferBase::memoryAlloc(const void *const pData, const GLsizeiptr size, const BufferUpdatePatternType updatePattern) noexcept
	{
		bind();
		glBufferData(__RAW_TYPE, size, pData, GLenum(updatePattern));

		__memAllocated = true;
		__memSize = size;
	}

	void BufferBase::memoryCopy(const void *const pData, const GLsizeiptr size, const GLintptr offset) noexcept
	{
		assert(isMemoryAllocated());

		bind();
		glBufferSubData(__RAW_TYPE, offset, size, pData);
	}

	void BufferBase::memoryAlloc(const GLsizeiptr size, const BufferUpdatePatternType updatePattern) noexcept
	{
		memoryAlloc(nullptr, size, updatePattern);

		if (__zeroInit)
			memorySet(0);
	}

	void BufferBase::memoryFree() noexcept
	{
		bind();
		glBufferData(__RAW_TYPE, 0, nullptr, GL_STATIC_DRAW);

		__memAllocated = false;
		__memSize = 0;
	}

	void BufferBase::memorySet(const uint8_t value) noexcept
	{
		assert(isMemoryAllocated());

		memset(mapHostInterface(BufferAccessType::WRITE_ONLY), 0, __memSize);
		unmapHostInterface();
	}

	void *BufferBase::mapHostInterface(const BufferAccessType accessType) noexcept
	{
		bind();

		void *const pRetVal = glMapBuffer(__RAW_TYPE, GLenum(accessType));
	
		return pRetVal;
	}

	void BufferBase::unmapHostInterface() noexcept
	{
		bind();
		glUnmapBuffer(__RAW_TYPE);
	}

	BufferBase &BufferBase::operator=(const BufferBase &src) noexcept
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

	BufferBase::~BufferBase() noexcept
	{
		__release();
	}
}