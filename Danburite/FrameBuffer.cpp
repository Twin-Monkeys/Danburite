#include "FrameBuffer.h"
#include <glm/gtc/type_ptr.hpp>
#include "RenderContext.h"

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

	FrameBuffer::FrameBuffer(const GLuint id) noexcept :
		BindableObject(id)
	{}

	FrameBuffer::FrameBuffer() :
		FrameBuffer(__createBufObj())
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
		FrameBuffer &target, const FrameBufferBlitFlag mask,
		const GLint srcLeft, const GLint srcBottom, const GLint srcRight, const GLint srcUp,
		const GLint targetLeft, const GLint targetBottom, const GLint targetRight, const GLint targetUp) noexcept
	{
		bind();
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, target.ID);
		glBlitFramebuffer(
			srcLeft, srcBottom, srcRight, srcUp,
			targetLeft, targetBottom, targetRight, targetUp,
			GLbitfield(mask), GL_NEAREST);

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, ID);
	}

	void FrameBuffer::blit(
		FrameBuffer& target, const FrameBufferBlitFlag mask, const GLint width, const GLint height) noexcept
	{
		blit(target, mask, 0, 0, width, height, 0, 0, width, height);
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

	void FrameBuffer::clearColorBuffer(const GLuint attachmentIndex, const GLfloat clearValue) noexcept
	{
		clearColorBuffer(attachmentIndex, { clearValue, clearValue, clearValue, clearValue });
	}

	void FrameBuffer::clearColorBuffer(const GLuint attachmentIndex, const vec4 &clearValue) noexcept
	{
		bind();
		// clear buffer는 state 변경이 아니므로 clear color가 저장되지 않음.
		glClearBufferfv(GL_COLOR, attachmentIndex, value_ptr(clearValue));
	}

	void FrameBuffer::clearDepthBuffer(const GLfloat clearValue) noexcept
	{
		ContextStateManager &stateMgr = RenderContext::getCurrentStateManager();
		stateMgr.setState(GLStateType::DEPTH_TEST, true);
		stateMgr.enableDepthMask(true);

		bind();
		glClearBufferfv(GL_DEPTH, 0, &clearValue);
	}

	void FrameBuffer::clearStencilBuffer(const GLuint clearValue) noexcept
	{
		ContextStateManager& stateMgr = RenderContext::getCurrentStateManager();
		stateMgr.setState(GLStateType::STENCIL_TEST, true);
		stateMgr.setStencilMask(0xFFU);

		bind();
		glClearBufferuiv(GL_STENCIL, 0, &clearValue);
	}

	void FrameBuffer::clearBuffers(const FrameBufferBlitFlag targets) noexcept
	{
		ContextStateManager &stateMgr = RenderContext::getCurrentStateManager();

		if (targets & FrameBufferBlitFlag::DEPTH)
		{
			stateMgr.setState(GLStateType::DEPTH_TEST, true);
			stateMgr.enableDepthMask(true);
		}

		if (targets & FrameBufferBlitFlag::STENCIL)
		{
			stateMgr.setState(GLStateType::STENCIL_TEST, true);
			stateMgr.setStencilMask(0xFFU);
		}

		bind();
		glClear(GLbitfield(targets));
	}

	FrameBuffer::~FrameBuffer()
	{
		__release();
	}

	FrameBuffer &FrameBuffer::getDefault() noexcept
	{
		static FrameBuffer defaultBuffer { 0 };
		return defaultBuffer;
	}

	void FrameBuffer::bindDefault() noexcept
	{
		getDefault().bind();
	}
}