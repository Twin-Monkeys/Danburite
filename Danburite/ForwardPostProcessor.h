#pragma once

#include "PostProcessor.h"
#include "RenderBuffer.h"

namespace Danburite
{
	class ForwardPostProcessor : public PostProcessor
	{
	private:
		std::unique_ptr<ObjectGL::AttachableTexture> __pColorAttachment;
		std::unique_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

	protected:
		ForwardPostProcessor(const ProgramType type);
		virtual void _onRender() noexcept override;

	public:
		ForwardPostProcessor();
		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~ForwardPostProcessor() = default;
	};
}