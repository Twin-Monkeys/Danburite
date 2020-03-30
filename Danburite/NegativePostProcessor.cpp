#include "NegativePostProcessor.h"
#include "ProgramFactory.h"

namespace Danburite
{
	NegativePostProcessor::NegativePostProcessor() :
		ForwardPostProcessor(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_NEGATIVE))
	{}
}