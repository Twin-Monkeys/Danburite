#include "MSAAPostProcessor.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	MSAAPostProcessor::MSAAPostProcessor(
		const GLsizei numSamplePoints, const bool fixedSampleLocations) :
		PostProcessor(ProgramType::POST_PROCESS_MSAA),
		NUM_SAMPLE_POINTS(numSamplePoints),
		FIXED_SAMPLE_LOCATIONS(fixedSampleLocations),
		__pColorAttachment(make_unique<TextureMultisample>()),
		__pDepthStencilAttachment(make_unique<RenderBufferMultisample>())
	{
		assert(NUM_SAMPLE_POINTS);
	}

	void MSAAPostProcessor::_onRender() noexcept
	{
		__pColorAttachment->bind(
			ShaderIdentifier::Value::PostProcess::COLOR_ATTACHMENT_ARRAY_LOCATION);
	}

	void MSAAPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__pColorAttachment->memoryAlloc(
			width, height, TextureInternalFormatType::RGB, NUM_SAMPLE_POINTS, FIXED_SAMPLE_LOCATIONS);

		__pDepthStencilAttachment->memoryAlloc(
			width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8, NUM_SAMPLE_POINTS);

		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pColorAttachment);
		_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
	}
}