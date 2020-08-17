#pragma once

#include "RenderingPipeline.h"

namespace Danburite
{
	class ForwardRenderingPipeline : public RenderingPipeline
	{
	private:
		SetupTransaction __setupTransaction;

	protected:
		virtual void _onRender(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<SceneObject> &drawer, Skybox &skybox, PostProcessorPipeline &ppPipeline) noexcept override;

	public:
		ForwardRenderingPipeline(
			LightManager &lightManager, PerspectiveCamera &camera, BatchProcessor<SceneObject> &drawer, Skybox &skybox);
	};
}
