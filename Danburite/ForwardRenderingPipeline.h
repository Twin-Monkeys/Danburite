#pragma once

#include "RenderingPipeline.h"
#include "UniformBufferFactory.h"

namespace Danburite
{
	class ForwardRenderingPipeline : public RenderingPipeline
	{
	private:
		DeferredUniformBuffer<PhongUniformInterface> &__phongUB =
			UniformBufferFactory::getInstance().getUniformBuffer<PhongUniformInterface>();

		SetupTransaction __setupTransaction;

	protected:
		virtual void _onRender(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<SceneObject> &drawer, Skybox* const pSkybox, PostProcessorPipeline &ppPipeline) noexcept override;

	public:
		ForwardRenderingPipeline(
			LightManager &lightManager, PerspectiveCamera &camera, BatchProcessor<SceneObject> &drawer, Skybox* const pSkybox = nullptr);
	};
}
