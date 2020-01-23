#include "RenderBuffer.h"
#include "AssertException.h"

namespace ObjectGL
{
	GLuint RenderBuffer::__createBufObj()
	{
		GLuint retVal;
		glGenRenderbuffers(1, &retVal);

		if (!retVal)
			throw RenderBufferException("Cannot create render buffer");

		return retVal;
	}

	RenderBuffer::RenderBuffer() :
		BindableObject(__createBufObj())
	{}

	void RenderBuffer::__release() noexcept
	{
		glDeleteRenderbuffers(1, &ID);
	}

	void RenderBuffer::_onBind() noexcept
	{
		glBindRenderbuffer(GL_RENDERBUFFER, ID);
	}

	void RenderBuffer::_onAttach(const AttachmentType type) noexcept
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GLenum(type), GL_RENDERBUFFER, ID);
	}

	void RenderBuffer::_onDetach(const AttachmentType type) noexcept
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GLenum(type), GL_RENDERBUFFER, 0);
	}

	void RenderBuffer::memoryAlloc(
		const GLsizei width, const GLsizei height, const RenderBufferInternalFormatType internalFormat) noexcept
	{
		bind();
		glRenderbufferStorage(GL_RENDERBUFFER, GLenum(internalFormat), width, height);
	}
}