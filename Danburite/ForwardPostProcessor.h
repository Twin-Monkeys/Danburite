#pragma once

#include "PostProcessor.h"
#include "Program.h"
#include "AttachableTextureRectangle.h"
#include "RenderBuffer.h"
#include "FullscreenDrawer.h"
#include "SetupTransaction.h"
#include "UniformBufferFactory.h"

namespace Danburite
{
	class ForwardPostProcessor : public PostProcessor
	{
	private:
		const bool __attachDepthBuffer;

		ObjectGL::Program &__program;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pColorAttachment;
		std::shared_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

		ObjectGL::UniformBuffer &__texContainerSetter =
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::TEX_CONTAINER);

		FullscreenDrawer &__fullscreenDrawer = FullscreenDrawer::getInstance();
		SetupTransaction __setupTransaction;

	protected:
		ForwardPostProcessor(ObjectGL::Program &program, const bool attachDepthBuffer);

		virtual void render(ObjectGL::FrameBuffer &renderTarget) noexcept override;

	public:
		ForwardPostProcessor(const bool attachDepthBuffer = false);
		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~ForwardPostProcessor() = default;
	};
}