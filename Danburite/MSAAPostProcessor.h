#pragma once

#include "PostProcessor.h"
#include "TextureMultisample.h"
#include "RenderBufferMultisample.h"

namespace Danburite
{
	class MSAAPostProcessor : public PostProcessor
	{
	private:
		std::unique_ptr<ObjectGL::TextureMultisample> __pColorAttachment;
		std::unique_ptr<ObjectGL::RenderBufferMultisample> __pDepthStencilAttachment;

	protected:
		virtual void _onRender() noexcept override;

	public:
		MSAAPostProcessor(const GLsizei numSamplePoints = 4, const bool fixedSampleLocations = true);
		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~MSAAPostProcessor() = default;
	};
}