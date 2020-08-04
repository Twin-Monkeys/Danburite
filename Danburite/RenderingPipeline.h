#pragma once

#include "RenderingPipelineType.h"
#include "PerspectiveCamera.h"
#include "BatchProcessor.h"
#include "PostProcessingPipeline.h"
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
		ObjectGL::UniformBuffer &__pipelineSetter;

		LightManager &__lightManager;
		PerspectiveCamera &__camera;
		BatchProcessor<SceneObject> &__drawer;
		PostProcessingPipeline &__ppPipeline;
		Skybox &__skybox;

	protected:
		virtual void _onSetScreenSize(const GLsizei width, const GLsizei height) noexcept;

		virtual void _onRender(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<SceneObject> &drawer, Skybox &skybox, PostProcessingPipeline &ppPipeline) noexcept = 0;

	public:
		RenderingPipeline(
			const RenderingPipelineType pipelineType,
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<SceneObject> &drawer, Skybox &skybox, PostProcessingPipeline &ppPipeline) noexcept;
		
		constexpr RenderingPipelineType getType() const noexcept;

		void setScreenSize(const GLsizei width, const GLsizei height) noexcept;
		constexpr const glm::ivec2 &getScreenSize() const noexcept;

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
}