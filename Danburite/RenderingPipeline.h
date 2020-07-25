#pragma once

#include "LightHandler.h"
#include "PerspectiveCamera.h"
#include "Drawer.h"
#include "PostProcessingPipeline.h"

namespace Danburite
{
	class RenderingPipeline abstract
	{
	protected:
		LightHandler &_lightHandler;
		ObjectGL::UniformBuffer &_cameraSetter;
		PerspectiveCamera &_camera;
		Drawer &_drawer;
		PostProcessingPipeline &_ppPipeline;

	public:
		RenderingPipeline(
			LightHandler &lightHandler, PerspectiveCamera &camera,
			Drawer &drawer, PostProcessingPipeline &ppPipeline) noexcept;
		
		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept = 0;
		virtual void render() noexcept = 0;
	};
}