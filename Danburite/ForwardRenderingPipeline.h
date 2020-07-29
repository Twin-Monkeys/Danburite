#pragma once

#include "RenderingPipeline.h"

namespace Danburite
{
	class ForwardRenderingPipeline : public RenderingPipeline
	{
	protected:
		virtual void _onRender(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<Drawable> &drawer, Skybox &skybox, PostProcessingPipeline &ppPipeline) noexcept override;

	public:
		ForwardRenderingPipeline(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<Drawable> &drawer, Skybox &skybox, PostProcessingPipeline &ppPipeline);
	};
}
