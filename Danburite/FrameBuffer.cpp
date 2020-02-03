#include "FrameBuffer.h"

using namespace std;

namespace ObjectGL
{
	GLuint FrameBuffer::__createBufObj()
	{
		GLuint retVal;
		glGenFramebuffers(1, &retVal);

		if (!retVal)
			throw FrameBufferException("Cannot create frame buffer");

		return retVal;
	}

	FrameBuffer::FrameBuffer() :
		BindableObject(__createBufObj())
	{}

	void FrameBuffer::__release() noexcept
	{
		glDeleteFramebuffers(1, &ID);
	}

	void FrameBuffer::_onBind() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, ID);
	}

	FrameBufferStatusType FrameBuffer::getStatus() noexcept
	{
		bind();
		return FrameBufferStatusType(glCheckFramebufferStatus(GL_FRAMEBUFFER));
	}

	void FrameBuffer::attach(const AttachmentType attachmentType, Attachable &attachment) noexcept
	{
		bind();
		__attachmentMap[attachmentType] = &attachment;

		attachment._onAttach(attachmentType);
	}

	bool FrameBuffer::detach(const AttachmentType attachmentType) noexcept
	{
		Attachable *&pAttachment = __attachmentMap[attachmentType];
		if (!pAttachment)
			return false;

		bind();
		pAttachment->_onDetach(attachmentType);
		pAttachment = nullptr;
		return true;
	}

	void FrameBuffer::blit(
		FrameBuffer* const pTarget, const FrameBufferBlitFlag mask,
		const GLint srcLeft, const GLint srcBottom, const GLint srcRight, const GLint srcUp,
		const GLint targetLeft, const GLint targetBottom, const GLint targetRight, const GLint targetUp) const noexcept
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, ID);

		GLuint targetObj = 0U;
		if (pTarget)
			targetObj = pTarget->ID;

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, targetObj);

		glBlitFramebuffer(
			srcLeft, srcBottom, srcRight, srcUp,
			targetLeft, targetBottom, targetRight, targetUp,
			GLbitfield(mask), GL_NEAREST);

		unbind();
	}

	void FrameBuffer::setInputColorBuffer(const ColorBufferType type) noexcept
	{
		bind();
		glReadBuffer(GLenum(type));
	}

	void FrameBuffer::setOutputColorBuffer(const ColorBufferType type) noexcept
	{
		bind();
		glDrawBuffer(GLenum(type));
	}

	FrameBuffer::~FrameBuffer()
	{
		__release();
	}

	void FrameBuffer::unbind() noexcept
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0U);
		_unbind();
	}
}