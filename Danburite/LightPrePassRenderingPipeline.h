#pragma once

#include "RenderingPipeline.h"

namespace Danburite
{
	class LightPrePassRenderingPipeline : public RenderingPipeline
	{
	private:
		AttachmentServer __attachmentServer;
		ObjectGL::VertexArray __fullscreenQuadVA { 6 };

		std::unique_ptr<ObjectGL::FrameBuffer> __pNormalShininessFB;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pPosAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pNormalSpecularAttachment;

		std::unique_ptr<ObjectGL::FrameBuffer> __pLightingFB;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pLightingAttachment;

		std::shared_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

		ObjectGL::Program &__extractionProgram;

	public:
		LightPrePassRenderingPipeline(
			LightHandler& lightHandler, PerspectiveCamera &camera,
			Drawer& drawer, PostProcessingPipeline& ppPipeline);

		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;
		virtual void render() noexcept override;
	};
}