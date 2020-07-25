#pragma once

#include "RenderingPipeline.h"

namespace Danburite
{
	class LightPrePassRenderingPipeline : public RenderingPipeline
	{
	private:
		AttachmentServer __attachmentServer;

		ObjectGL::Program &__extractionProgram;

	public:
		LightPrePassRenderingPipeline(
			LightHandler& lightHandler, PerspectiveCamera &camera,
			Drawer& drawer, PostProcessingPipeline& ppPipeline);

		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;
		virtual void render() noexcept override;
	};
}