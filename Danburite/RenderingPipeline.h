#pragma once

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

		PostProcessorPipeline __ppPipeline;

		LightManager &__lightManager;
		PerspectiveCamera &__camera;
		BatchProcessor<SceneObject> &__drawer;
		Skybox * const __pSkybox;

	protected:
		virtual void _onSetScreenSize(const GLsizei width, const GLsizei height) noexcept;

		virtual void _onRender(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<SceneObject> &drawer, Skybox *const pSkybox, PostProcessorPipeline &ppPipeline) noexcept = 0;

	public:
		RenderingPipeline(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<SceneObject> &drawer, Skybox *const pSkybox = nullptr) noexcept;
		
		void setScreenSize(const GLsizei width, const GLsizei height) noexcept;
		constexpr const glm::ivec2 &getScreenSize() const noexcept;

		constexpr void setRenderTarget(ObjectGL::FrameBuffer &target) noexcept;

		constexpr PostProcessorPipeline &getPostProcessorPipeline() noexcept;
		constexpr const PostProcessorPipeline &getPostProcessorPipeline() const noexcept;

		void render() noexcept;
	};

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