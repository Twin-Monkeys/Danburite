#pragma once

#include "BindableObject.h"
#include "Attachable.h"
#include "RenderBufferException.h"
#include "RenderBufferInternalFormatType.h"

namespace ObjectGL
{
	class RenderBuffer : public BindableObject<RenderBuffer, GLuint>, public Attachable
	{
	private:
		RenderBuffer(const RenderBuffer &) = delete;
		RenderBuffer &operator=(const RenderBuffer &) = delete;

		void __release() noexcept;

		static GLuint __createBufObj();

	protected:
		virtual void _onBind() noexcept override;

		virtual void _onAttach(const AttachmentType type) noexcept override;
		virtual void _onDetach(const AttachmentType type) noexcept override;

	public:
		RenderBuffer();

		void memoryAlloc(
			const GLsizei width, const GLsizei height, const RenderBufferInternalFormatType internalFormat) noexcept;

		virtual ~RenderBuffer() = default;
	};
}