#include "NegativePostProcessor.h"
#include "ProgramFactory.h"

namespace Danburite
{
	NegativePostProcessor::NegativePostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_NEGATIVE), attachDepthBuffer)
	{}
}