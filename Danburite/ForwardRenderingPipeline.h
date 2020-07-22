#pragma once

#include "RenderingPipeline.h"

namespace Danburite
{
	class ForwardRenderingPipeline : public RenderingPipeline
	{
	public:
		ForwardRenderingPipeline(
			LightHandler &lightHandler, Camera &camera,
			Drawer &drawer, PostProcessingPipeline &ppPipeline);

		virtual void render() noexcept override;
	};
}
