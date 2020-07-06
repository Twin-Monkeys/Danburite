#pragma once

#include "PostProcessor.h"
#include "AttachableTexture2D.h"
#include "RenderBuffer.h"

namespace Danburite
{
	class BloomPostProcessor : public PostProcessor
	{
	private:
		ObjectGL::Program &__program;
		std::unique_ptr<ObjectGL::AttachableTexture2D> __pColorAttachment;
		std::unique_ptr<ObjectGL::AttachableTexture2D> __pExtractedColorAttachment;
		std::unique_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

	protected:
		virtual void _onRender(
			ObjectGL::UniformBuffer &attachmentSetter, ObjectGL::VertexArray &fullscreenQuadVA) noexcept override;

	public:
		BloomPostProcessor();
		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~BloomPostProcessor() = default;
	};
}