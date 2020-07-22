#pragma once

#include "LightHandler.h"
#include "Camera.h"
#include "Drawer.h"
#include "PostProcessingPipeline.h"

namespace Danburite
{
	class RenderingPipeline abstract
	{
	protected:
		LightHandler &_lightHandler;
		ObjectGL::UniformBuffer &_cameraSetter;
		Camera &_camera;
		Drawer &_drawer;
		PostProcessingPipeline &_ppPipeline;

	public:
		RenderingPipeline(
			LightHandler &lightHandler, Camera &camera,
			Drawer &drawer, PostProcessingPipeline &ppPipeline) noexcept;
		
		virtual void render() noexcept = 0;
	};
}