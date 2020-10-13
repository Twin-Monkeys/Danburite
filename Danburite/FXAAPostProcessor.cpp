#include "FXAAPostProcessor.h"
#include "ProgramFactory.h"

using namespace ObjectGL;

namespace Danburite
{
	FXAAPostProcessor::FXAAPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor { ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_FXAA), attachDepthBuffer }
	{
		setEdgeSteps(Constant::FXAA::DEFAULT_EDGE_STEPS, Constant::FXAA::DEFAULT_NUM_EDGE_STEPS);

		__setup.setup([this](ContextStateManager &stateMgr)
		{
			FXAAUniformInterface &fxaaUI = __fxaaUB.getInterface();

			fxaaUI.numEdgeSteps = __numEdgeSteps;
			fxaaUI.edgeSteps = { 0ULL, size_t { __numEdgeSteps }, __edgeSteps };

			fxaaUI.absoluteThreshold = __absoluteThreshold;
			fxaaUI.relativeThreshold = __relativeThreshold;
			fxaaUI.subpixelBlendingFactor = __subpixelBlendingFactor;

			__fxaaUB.selfDeploy();
		});
	}

	void FXAAPostProcessor::setEdgeSteps(const float* const pEdgeSteps, const size_t numEdgeStep) noexcept
	{
		__numEdgeSteps = unsigned(numEdgeStep);
		std::memcpy(__edgeSteps, pEdgeSteps, sizeof(float) * numEdgeStep);
	}

	void FXAAPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__setup();
		ForwardPostProcessor::render(renderTarget);
	}
}