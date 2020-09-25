#pragma once

#include "RenderingPipeline.h"
#include "FullscreenDrawer.h"
#include "SetupTransaction.h"
#include "UniformBufferFactory.h"
#include "PhongUniformInterface.h"
#include "TextureContainerUniformInterface.h"
#include "LightPrePassUniformInterface.h"
#include "ProgramFactory.h"

namespace Danburite
{
	class LightPrePassRenderingPipeline : public RenderingPipeline
	{
	private:
		AttachmentServer __attachmentServer;

		DeferredUniformBuffer<PhongUniformInterface> &__phongUB =
			UniformBufferFactory::getInstance().getUniformBuffer<PhongUniformInterface>();

		DeferredUniformBuffer<TextureContainerUniformInterface> &__texContainerUB =
			UniformBufferFactory::getInstance().getUniformBuffer<TextureContainerUniformInterface>();

		DeferredUniformBuffer<LightPrePassUniformInterface> &__lightPrePassUB =
			UniformBufferFactory::getInstance().getUniformBuffer<LightPrePassUniformInterface>();

		ObjectGL::Program &__geometryProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::LIGHT_PREPASS_GEOMETRY_EXTRACTION);

		ObjectGL::Program &__ssaoProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::SSAO);

		ObjectGL::Program &__ssaoBlurProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::SSAO_POST_PROCESSING);

		ObjectGL::Program &__lightingProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::LIGHT_PREPASS_LIGHTING);

		FullscreenDrawer &__fullscreenDrawer = FullscreenDrawer::getInstance();

		std::unique_ptr<ObjectGL::FrameBuffer> __pPosNormalShininessFB = std::make_unique<ObjectGL::FrameBuffer>();
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pPosAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pNormalShininessAttachment;
		std::shared_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

		std::unique_ptr<ObjectGL::FrameBuffer> __pSSAOFB = std::make_unique<ObjectGL::FrameBuffer>();
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pAOInvAttachment;

		std::unique_ptr<ObjectGL::FrameBuffer> __pSSAOPPFB = std::make_unique<ObjectGL::FrameBuffer>();
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pAOInvPPAttachment;

		std::unique_ptr<ObjectGL::FrameBuffer> __pLightingFB = std::make_unique<ObjectGL::FrameBuffer>();
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pLightAmbientAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pLightDiffuseAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pLightSpecularAttachment;

		SetupTransaction __geometryPassSetup;
		SetupTransaction __ssaoSetup;
		SetupTransaction __ssaoPPSetup;
		SetupTransaction __lightingPassSetup;
		SetupTransaction __compositionPassSetup;

	protected:
		virtual void _onSetScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual void _onRender(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<SceneObject> &drawer, Skybox *const pSkybox, PostProcessorPipeline &ppPipeline) noexcept override;

	public:
		LightPrePassRenderingPipeline(
			LightManager &lightManager, PerspectiveCamera &camera, BatchProcessor<SceneObject> &drawer, Skybox *const pSkybox = nullptr);
	};
}