#pragma once

#include "PostProcessor.h"
#include "AttachableTextureRectangle.h"
#include "RenderBuffer.h"

namespace Danburite
{
	class ForwardPostProcessor : public PostProcessor
	{
	private:
		ObjectGL::Program &__program;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pColorAttachment;
		std::unique_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

	protected:
		ForwardPostProcessor(ObjectGL::Program &program, const bool attachDepthBuffer);

		virtual void _onRender(
			ObjectGL::UniformBuffer &attachmentSetter, ObjectGL::VertexArray &fullscreenQuadVA) noexcept override;

	public:
		ForwardPostProcessor(const bool attachDepthBuffer = false);
		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~ForwardPostProcessor() = default;
	};
}