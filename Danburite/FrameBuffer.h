#pragma once

#include "BindableObject.h"
#include "FrameBufferException.h"
#include "FrameBufferStatusType.h"
#include "Texture2D.h"
#include "Attachable.h"

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

		virtual ~FrameBuffer() noexcept;

		static void unbind() noexcept;
	};
}