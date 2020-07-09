#include "FrameBuffer.h"
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

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

		const FrameBufferStatusType retVal =
			FrameBufferStatusType(glCheckFramebufferStatus(GL_FRAMEBUFFER));

		return retVal;
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

	void FrameBuffer::setOutputColorBuffers(const initializer_list<ColorBufferType> &types) noexcept
	{
		bind();
		glDrawBuffers(GLsizei(types.size()), reinterpret_cast<const GLenum *>(types.begin()));
	}

	void FrameBuffer::clearColorBuffer(const GLuint attachmentIndex, const vec4 &clearValue)
	{
		bind();
		glClearBufferfv(GL_COLOR, attachmentIndex, value_ptr(clearValue));
	}

	void FrameBuffer::clearDepthBuffer(const GLfloat clearValue)
	{
		bind();
		glClearBufferfv(GL_DEPTH, 0, &clearValue);
	}

	void FrameBuffer::clearStencilBuffer(const GLuint clearValue)
	{
		bind();
		glClearBufferuiv(GL_STENCIL, 0, &clearValue);
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