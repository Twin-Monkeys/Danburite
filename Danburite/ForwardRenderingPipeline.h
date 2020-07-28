#pragma once

#include "RenderingPipeline.h"

namespace Danburite
{
	class ForwardRenderingPipeline : public RenderingPipeline
	{
	protected:
		virtual void _onRender(
			LightHandler &lightHandler, ObjectGL::UniformBuffer &cameraSetter,
			PerspectiveCamera &camera, Drawer &drawer, PostProcessingPipeline &ppPipeline) noexcept override;

	public:
		ForwardRenderingPipeline(
			LightHandler &lightHandler, PerspectiveCamera &camera,
			Drawer &drawer, PostProcessingPipeline &ppPipeline);
	};
}
