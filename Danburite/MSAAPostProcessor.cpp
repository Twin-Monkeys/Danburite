#include "MSAAPostProcessor.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	MSAAPostProcessor::MSAAPostProcessor(
		const GLsizei numSamplePoints, const bool fixedSampleLocations) :
		PostProcessor(ProgramType::POST_PROCESS_MSAA),
		__pColorAttachment(make_unique<TextureMultisample>()),
		__pDepthStencilAttachment(make_unique<RenderBufferMultisample>())
	{}

	void MSAAPostProcessor::_onRender() noexcept
	{
		__pColorAttachment->bind(
			ShaderIdentifier::Value::PostProcess::COLOR_ATTACHMENT_ARRAY_LOCATION);
	}

	void MSAAPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{

	}
}