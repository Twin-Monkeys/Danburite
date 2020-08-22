#pragma once

#include "RenderingPipeline.h"
#include "FullscreenDrawer.h"
#include "SetupTransaction.h"
#include "UniformBufferFactory.h"
#include "ProgramFactory.h"

namespace Danburite
{
	class LightPrePassRenderingPipeline : public RenderingPipeline
	{
	private:
		AttachmentServer __attachmentServer;

		ObjectGL::UniformBuffer &__phongSetter =
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::PHONG);

		ObjectGL::UniformBuffer &__texContainerSetter =
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::TEX_CONTAINER);

		ObjectGL::UniformBuffer &__lightPrePassSetter =
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::LIGHT_PREPASS);

		ObjectGL::Program &__geometryProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::LIGHT_PREPASS_GEOMETRY_EXTRACTION);

		ObjectGL::Program &__lightingProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::LIGHT_PREPASS_LIGHTING);

		FullscreenDrawer &__fullscreenDrawer = FullscreenDrawer::getInstance();

		std::unique_ptr<ObjectGL::FrameBuffer> __pPosNormalShininessFB = std::make_unique<ObjectGL::FrameBuffer>();
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pPosAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pNormalShininessAttachment;
		std::shared_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

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