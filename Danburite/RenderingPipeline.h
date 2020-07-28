#pragma once

#include "RenderingPipelineType.h"
#include "LightHandler.h"
#include "PerspectiveCamera.h"
#include "Drawer.h"
#include "PostProcessingPipeline.h"

namespace Danburite
{
	class RenderingPipeline abstract
	{
	private:
		glm::ivec2 __screenSize { 0, 0 };

		const RenderingPipelineType __TYPE;
		ObjectGL::UniformBuffer &__pipelineSetter;

		LightHandler &__lightHandler;
		ObjectGL::UniformBuffer &__cameraSetter;
		PerspectiveCamera &__camera;
		Drawer &__drawer;
		PostProcessingPipeline &__ppPipeline;

	protected:
		virtual void _onSetScreenSize(const GLsizei width, const GLsizei height) noexcept;

		virtual void _onRender(
			LightHandler &lightHandler, ObjectGL::UniformBuffer &cameraSetter,
			PerspectiveCamera &camera, Drawer &drawer, PostProcessingPipeline &ppPipeline) noexcept = 0;

	public:
		RenderingPipeline(
			const RenderingPipelineType pipelineType,
			LightHandler &lightHandler, PerspectiveCamera &camera,
			Drawer &drawer, PostProcessingPipeline &ppPipeline) noexcept;
		
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