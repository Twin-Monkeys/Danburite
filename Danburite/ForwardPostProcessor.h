#pragma once

#include "PostProcessor.h"
#include "AttachableTextureRectangle.h"
#include "RenderBuffer.h"
#include "SetupTransaction.h"

namespace Danburite
{
	class ForwardPostProcessor : public PostProcessor
	{
	private:
		const bool __attachDepthBuffer;

		ObjectGL::Program &__program;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pColorAttachment;
		std::shared_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

		SetupTransaction __setupTransaction;

	protected:
		ForwardPostProcessor(ObjectGL::Program &program, const bool attachDepthBuffer);

		virtual void _onRender(
			ObjectGL::FrameBuffer &renderTarget,
			ObjectGL::UniformBuffer &texContainerSetter, FullscreenDrawer &fullscreenDrawer) noexcept override;

	public:
		ForwardPostProcessor(const bool attachDepthBuffer = false);
		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~ForwardPostProcessor() = default;
	};
}