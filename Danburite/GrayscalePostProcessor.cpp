#include "GrayscalePostProcessor.h"
#include "ProgramFactory.h"

namespace Danburite
{
	GrayscalePostProcessor::GrayscalePostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_GRAYSCALE), attachDepthBuffer)
	{}
}