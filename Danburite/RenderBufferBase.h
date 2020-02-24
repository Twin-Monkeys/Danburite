#pragma once

#include "BindableObject.h"
#include "Attachable.h"
#include "RenderBufferException.h"
#include "RenderBufferInternalFormatType.h"

namespace ObjectGL
{
	class RenderBufferBase abstract : public BindableObject<RenderBufferBase, GLuint>, public Attachable
	{
	private:
		RenderBufferBase(const RenderBufferBase &) = delete;
		RenderBufferBase &operator=(const RenderBufferBase &) = delete;

		void __release() noexcept;

		static GLuint __createBufObj();

	protected:
		virtual void _onAttach(const AttachmentType type) noexcept override;
		virtual void _onDetach(const AttachmentType type) noexcept override;

		virtual void _onBind() noexcept override;

	public:
		RenderBufferBase();

		virtual ~RenderBufferBase() = default;
	};
}