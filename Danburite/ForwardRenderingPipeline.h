#pragma once

#include "RenderingPipeline.h"

namespace Danburite
{
	class ForwardRenderingPipeline : public RenderingPipeline
	{
	public:
		ForwardRenderingPipeline(
			LightHandler &lightHandler, PerspectiveCamera &camera,
			Drawer &drawer, PostProcessingPipeline &ppPipeline);

		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;
		virtual void render() noexcept override;
	};
}
