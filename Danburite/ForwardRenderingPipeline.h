#pragma once

#include "RenderingPipeline.h"

namespace Danburite
{
	class ForwardRenderingPipeline : public RenderingPipeline
	{
	protected:
		virtual void _onRender(
			LightManager &lightManager, ObjectGL::UniformBuffer &cameraSetter,
			PerspectiveCamera &camera, BatchProcessor<Drawable> &drawer, PostProcessingPipeline &ppPipeline) noexcept override;

	public:
		ForwardRenderingPipeline(
			LightManager &lightManager, PerspectiveCamera &camera,
			BatchProcessor<Drawable> &drawer, PostProcessingPipeline &ppPipeline);
	};
}
