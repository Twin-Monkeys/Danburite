#include "HDRPostProcessor.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"

using namespace ObjectGL;

namespace Danburite
{
	HDRPostProcessor::HDRPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_HDR), attachDepthBuffer)
	{
		__setupTransaction.setup([this](ContextStateManager &stateMgr)
		{
			__hdrSetter.setUniformFloat(
				ShaderIdentifier::Name::HDR::EXPOSURE, __exposure);
		});
	}

	void HDRPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__setupTransaction();
		ForwardPostProcessor::render(renderTarget);
	}
}