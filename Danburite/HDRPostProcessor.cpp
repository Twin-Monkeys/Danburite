#include "HDRPostProcessor.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"

using namespace ObjectGL;

namespace Danburite
{
	HDRPostProcessor::HDRPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_HDR), attachDepthBuffer),

		__hdrSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::HDR))
	{}

	void HDRPostProcessor::_onRender(
		PostProcessor* const pBoundProcessor,
		UniformBuffer &texContainerSetter, FullscreenDrawer &fullscreenDrawer) noexcept
	{
		__hdrSetter.setUniformFloat(ShaderIdentifier::Name::HDR::EXPOSURE, __exposure);
		ForwardPostProcessor::_onRender(pBoundProcessor, texContainerSetter, fullscreenDrawer);
	}
}