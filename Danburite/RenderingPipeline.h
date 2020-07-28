#pragma once

#include "RenderingPipelineType.h"
#include "PerspectiveCamera.h"
#include "BatchProcessor.h"
#include "PostProcessingPipeline.h"
#include "LightManager.h"
#include "Drawable.h"

namespace Danburite
{
	class RenderingPipeline abstract
	{
	private:
		glm::ivec2 __screenSize { 0, 0 };

		const RenderingPipelineType __TYPE;
		ObjectGL::UniformBuffer &__pipelineSetter;
		ObjectGL::UniformBuffer &__cameraSetter;

		LightManager &__lightManager;
		PerspectiveCamera &__camera;
		BatchProcessor<Drawable> &__drawer;
		PostProcessingPipeline &__ppPipeline;

	protected:
		virtual void _onSetScreenSize(const GLsizei width, const GLsizei height) noexcept;

		virtual void _onRender(
			LightManager &lightManager, ObjectGL::UniformBuffer &cameraSetter,
			PerspectiveCamera &camera, BatchProcessor<Drawable> &drawer, PostProcessingPipeline &ppPipeline) noexcept = 0;

	public:
		RenderingPipeline(
			const RenderingPipelineType pipelineType,
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<Drawable> &drawer, PostProcessingPipeline &ppPipeline) noexcept;
		
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