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
	{
		__setupTransaction.setSetupFunction([this](ContextStateManager &stateMgr)
		{
			__hdrSetter.setUniformFloat(
				ShaderIdentifier::Name::HDR::EXPOSURE, __exposure);
		});
	}

	void HDRPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__setupTransaction.setup();
		ForwardPostProcessor::render(renderTarget);
	}
}