#pragma once

#include "RenderingPipelineType.h"
#include "PerspectiveCamera.h"
#include "BatchProcessor.h"
#include "PostProcessorPipeline.h"
#include "SceneObject.h"
#include "LightManager.h"
#include "Skybox.h"

namespace Danburite
{
	class RenderingPipeline abstract
	{
	private:
		glm::ivec2 __screenSize { 0, 0 };

		const RenderingPipelineType __TYPE;

		ObjectGL::UniformBuffer &__pipelineSetter =
			UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::RENDERING_PIPELINE);

		PostProcessorPipeline __ppPipeline;

		LightManager &__lightManager;
		PerspectiveCamera &__camera;
		BatchProcessor<SceneObject> &__drawer;
		Skybox &__skybox;

	protected:
		virtual void _onSetScreenSize(const GLsizei width, const GLsizei height) noexcept;

		virtual void _onRender(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<SceneObject> &drawer, Skybox &skybox, PostProcessorPipeline &ppPipeline) noexcept = 0;

	public:
		RenderingPipeline(
			const RenderingPipelineType pipelineType, LightManager &lightManager,
			PerspectiveCamera &camera, BatchProcessor<SceneObject> &drawer, Skybox &skybox) noexcept;
		
		constexpr RenderingPipelineType getType() const noexcept;

		void setScreenSize(const GLsizei width, const GLsizei height) noexcept;
		constexpr const glm::ivec2 &getScreenSize() const noexcept;

		constexpr void setRenderTarget(ObjectGL::FrameBuffer &target) noexcept;

		constexpr PostProcessorPipeline &getPostProcessorPipeline() noexcept;
		constexpr const PostProcessorPipeline &getPostProcessorPipeline() const noexcept;

		void render() noexcept;
	};

	constexpr RenderingPipelineType RenderingPipeline::getType() const noexcept
	{
		return __TYPE;
	}

	constexpr const glm::ivec2 &RenderingPipeline::getScreenSize() const noexcept
	{
		return __screenSize;
	}

	constexpr PostProcessorPipeline &RenderingPipeline::getPostProcessorPipeline() noexcept
	{
		return __ppPipeline;
	}

	constexpr const PostProcessorPipeline &RenderingPipeline::getPostProcessorPipeline() const noexcept
	{
		return __ppPipeline;
	}
}