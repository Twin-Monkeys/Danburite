#pragma once

#include "BindableObject.h"
#include "FrameBufferException.h"
#include "FrameBufferStatusType.h"
#include "Attachable.h"
#include "FrameBufferBlitFlag.h"
#include "ColorBufferType.h"
#include <glm/glm.hpp>

namespace ObjectGL
{
	class FrameBuffer : public BindableObject<FrameBuffer, GLuint>
	{
	private:
		std::unordered_map<AttachmentType, Attachable *> __attachmentMap;

		FrameBuffer(const FrameBuffer &) = delete;
		FrameBuffer &operator=(const FrameBuffer &) = delete;

		void __release() noexcept;

		static GLuint __createBufObj();

	protected:
		virtual void _onBind() noexcept override;

	public:
		FrameBuffer();

		FrameBufferStatusType getStatus() noexcept;
		void attach(const AttachmentType attachmentType, Attachable &attachment) noexcept;
		bool detach(const AttachmentType attachmentType) noexcept;

		void blit(
			FrameBuffer* const pTarget, const FrameBufferBlitFlag mask,
			const GLint srcLeft, const GLint srcBottom, const GLint srcRight, const GLint srcUp,
			const GLint targetLeft, const GLint targetBottom, const GLint targetRight, const GLint targetUp) const noexcept;

		void setInputColorBuffer(const ColorBufferType type) noexcept;
		void setOutputColorBuffer(const ColorBufferType type) noexcept;
		void setOutputColorBuffers(const std::initializer_list<ColorBufferType> &types) noexcept;

		void clearColorBuffer(const GLuint attachmentIndex, const glm::vec4 &clearValue);
		void clearDepthBuffer(const GLfloat	clearValue);
		void clearStencilBuffer(const GLuint clearValue);

		virtual ~FrameBuffer() noexcept;

		static void unbind() noexcept;
	};
}