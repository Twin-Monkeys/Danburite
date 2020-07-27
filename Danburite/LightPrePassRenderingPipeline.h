#pragma once

#include "RenderingPipeline.h"

namespace Danburite
{
	class LightPrePassRenderingPipeline : public RenderingPipeline
	{
	private:
		AttachmentServer __attachmentServer;
		ObjectGL::UniformBuffer &__texContainerSetter;

		ObjectGL::VertexArray __fullscreenQuadVA { 6 };

		ObjectGL::Program &__geometryProgram;
		std::unique_ptr<ObjectGL::FrameBuffer> __pNormalShininessFB;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pPosAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pNormalSpecularAttachment;
		std::shared_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

		ObjectGL::Program &__lightingProgram;
		std::unique_ptr<ObjectGL::FrameBuffer> __pLightingFB;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pAmbientAttenuationAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pDiffuseOcclusionInvAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pSpecularAttachment;

	public:
		LightPrePassRenderingPipeline(
			LightHandler& lightHandler, PerspectiveCamera &camera,
			Drawer& drawer, PostProcessingPipeline& ppPipeline);

		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;
		virtual void render() noexcept override;
	};
}