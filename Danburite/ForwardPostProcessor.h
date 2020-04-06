#pragma once

#include "PostProcessor.h"
#include "AttachableTexture2D.h"
#include "RenderBuffer.h"

namespace Danburite
{
	class ForwardPostProcessor : public PostProcessor
	{
	private:
		ObjectGL::Program &__program;
		std::unique_ptr<ObjectGL::AttachableTexture2D> __pColorAttachment;
		std::unique_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

	protected:
		ForwardPostProcessor(ObjectGL::Program &program);

		virtual void _onRender(
			ObjectGL::UniformSetter &attachmentSetter, ObjectGL::VertexArray &fullscreenQuadVA) noexcept override;

	public:
		ForwardPostProcessor();
		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~ForwardPostProcessor() = default;
	};
}