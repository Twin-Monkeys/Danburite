#include "ForwardPostProcessor.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ForwardPostProcessor::ForwardPostProcessor(const ProgramType type) :
		PostProcessor(type),
		__pColorAttachment(make_unique<AttachableTexture>()),
		__pDepthStencilAttachment(make_unique<RenderBuffer>())
	{}

	ForwardPostProcessor::ForwardPostProcessor() :
		ForwardPostProcessor(ProgramType::POST_PROCESS_FORWARD)
	{}

	void ForwardPostProcessor::_onRender() noexcept
	{
		__pColorAttachment->bind(
			ShaderIdentifier::Value::PostProcess::COLOR_ATTACHMENT_ARRAY_LOCATION);
	}

	void ForwardPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__pColorAttachment->memoryAlloc(
			width, height, TextureInternalFormatType::RGB, TextureExternalFormatType::RGB);

		__pDepthStencilAttachment->memoryAlloc(
			width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pColorAttachment);
		_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
	}
}