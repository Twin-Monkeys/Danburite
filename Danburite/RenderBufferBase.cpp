#include "RenderBufferBase.h"
#include <cassert>

namespace ObjectGL
{
	GLuint RenderBufferBase::__createBufObj()
	{
		GLuint retVal;
		glGenRenderbuffers(1, &retVal);

		if (!retVal)
			throw RenderBufferException("Cannot create render buffer");

		return retVal;
	}

	RenderBufferBase::RenderBufferBase() :
		BindableObject(__createBufObj())
	{}

	void RenderBufferBase::__release() noexcept
	{
		glDeleteRenderbuffers(1, &ID);
	}

	void RenderBufferBase::_onAttach(const AttachmentType type) noexcept
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GLenum(type), GL_RENDERBUFFER, ID);
	}

	void RenderBufferBase::_onDetach(const AttachmentType type) noexcept
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GLenum(type), GL_RENDERBUFFER, 0);
	}

	void RenderBufferBase::_onBind() noexcept
	{
		glBindRenderbuffer(GL_RENDERBUFFER, ID);
	}
}