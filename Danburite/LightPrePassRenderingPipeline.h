#pragma once

#include "RenderingPipeline.h"

namespace Danburite
{
	class LightPrePassRenderingPipeline : public RenderingPipeline
	{
	public:
		LightPrePassRenderingPipeline(
			LightHandler& lightHandler, Camera& camera,
			Drawer& drawer, PostProcessingPipeline& ppPipeline);

		virtual void render() noexcept override;
	};
}