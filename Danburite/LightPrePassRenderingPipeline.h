#pragma once

#include "RenderingPipeline.h"
#include "FullscreenDrawer.h"
#include "SetupTransaction.h"
#include "UniformBufferFactory.h"
#include "PhongUniformInterface.h"
#include "TextureContainerUniformInterface.h"
#include "SSAOUniformInterface.h"
#include "LightPrePassUniformInterface.h"
#include "ProgramFactory.h"
#include "SSAOException.h"

namespace Danburite
{
	class LightPrePassRenderingPipeline : public RenderingPipeline
	{
	private:
		bool __ssaoEnabled = false;
		GLfloat __ssaoSamplingRadius = Constant::SSAO::SAMPLING_RADIUS;
		GLfloat __ssaoStrength = Constant::SSAO::STRENGTH;
		GLuint __ssaoNumSamples = Constant::SSAO::NUM_SAMPLES;
		GLuint __ssaoBlurRange = Constant::SSAO::BLUR_RANGE;

		AttachmentServer __attachmentServer;

		DeferredUniformBuffer<PhongUniformInterface> &__phongUB =
			UniformBufferFactory::getInstance().getUniformBuffer<PhongUniformInterface>();

		DeferredUniformBuffer<TextureContainerUniformInterface> &__texContainerUB =
			UniformBufferFactory::getInstance().getUniformBuffer<TextureContainerUniformInterface>();

		DeferredUniformBuffer<SSAOUniformInterface> &__ssaoUB =
			UniformBufferFactory::getInstance().getUniformBuffer<SSAOUniformInterface>();

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

		constexpr bool isSSAOEnabled() const noexcept;
		constexpr void enableSSAO(const bool enabled) noexcept;

		constexpr GLfloat getSSAOSamplingRadius() const noexcept;
		constexpr void setSSAOSamplingRadius(const GLfloat radius) noexcept;

		constexpr GLfloat getSSAOStrength() const noexcept;
		constexpr void setSSAOStrength(const GLfloat strength) noexcept;

		constexpr GLuint getSSAONumSamples() const noexcept;
		void setSSAONumSamples(const GLuint numSamples);

		constexpr GLuint getSSAOBlurRange() const noexcept;
		constexpr void setSSAOBlurRange(const GLuint blurRange) noexcept;
	};

	constexpr bool LightPrePassRenderingPipeline::isSSAOEnabled() const noexcept
	{
		return __ssaoEnabled;
	}

	constexpr void LightPrePassRenderingPipeline::enableSSAO(const bool enabled) noexcept
	{
		__ssaoEnabled = enabled;
	}

	constexpr GLfloat LightPrePassRenderingPipeline::getSSAOSamplingRadius() const noexcept
	{
		return __ssaoSamplingRadius;
	}

	constexpr void LightPrePassRenderingPipeline::setSSAOSamplingRadius(const GLfloat radius) noexcept
	{
		__ssaoSamplingRadius = radius;
	}

	constexpr GLfloat LightPrePassRenderingPipeline::getSSAOStrength() const noexcept
	{
		return __ssaoStrength;
	}

	constexpr void LightPrePassRenderingPipeline::setSSAOStrength(const GLfloat strength) noexcept
	{
		__ssaoStrength = strength;
	}

	constexpr GLuint LightPrePassRenderingPipeline::getSSAONumSamples() const noexcept
	{
		return __ssaoNumSamples;
	}

	constexpr GLuint LightPrePassRenderingPipeline::getSSAOBlurRange() const noexcept
	{
		return __ssaoBlurRange;
	}

	constexpr void LightPrePassRenderingPipeline::setSSAOBlurRange(const GLuint blurRange) noexcept
	{
		__ssaoBlurRange = blurRange;
	}
}