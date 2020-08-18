#pragma once

#include "RenderingPipeline.h"
#include "FullscreenDrawer.h"
#include "SetupTransaction.h"

namespace Danburite
{
	class LightPrePassRenderingPipeline : public RenderingPipeline
	{
	private:
		AttachmentServer __attachmentServer;
		ObjectGL::UniformBuffer &__texContainerSetter;
		ObjectGL::UniformBuffer &__lightPrePassSetter;

		FullscreenDrawer &__fullscreenDrawer;

		ObjectGL::Program &__geometryProgram;
		std::unique_ptr<ObjectGL::FrameBuffer> __pNormalShininessFB = std::make_unique<ObjectGL::FrameBuffer>();
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pPosAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pNormalShininessAttachment;
		std::shared_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

		ObjectGL::Program &__lightingProgram;
		std::unique_ptr<ObjectGL::FrameBuffer> __pLightingFB = std::make_unique<ObjectGL::FrameBuffer>();
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pLightAmbientAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pLightDiffuseAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pLightSpecularAttachment;

		SetupTransaction __geometryPassSetup;
		SetupTransaction __lightingPassSetup;
		SetupTransaction __compositionPassSetup;

	protected:
		virtual void _onSetScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual void _onRender(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<SceneObject> &drawer, Skybox &skybox, PostProcessorPipeline &ppPipeline) noexcept override;

	public:
		LightPrePassRenderingPipeline(
			LightManager &lightManager, PerspectiveCamera &camera, BatchProcessor<SceneObject> &drawer, Skybox &skybox);
	};
}