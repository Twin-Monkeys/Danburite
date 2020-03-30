#include "GrayscalePostProcessor.h"
#include "ProgramFactory.h"

namespace Danburite
{
	GrayscalePostProcessor::GrayscalePostProcessor() :
		ForwardPostProcessor(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_GRAYSCALE))
	{}
}