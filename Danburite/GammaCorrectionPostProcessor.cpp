#include "GammaCorrectionPostProcessor.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "Material.h"

using namespace ObjectGL;

namespace Danburite
{
	GammaCorrectionPostProcessor::GammaCorrectionPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor { ProgramFactory::getInstance().
		getProgram(ProgramType::POST_PROCESS_GAMMA_CORRECTION), attachDepthBuffer }
	{
		__setupTransaction.setup([this](ContextStateManager &stateMgr)
		{
			MaterialUniformInterface &materialUI = __materialUB.getInterface();
			materialUI.gamma = __gamma;
			__materialUB.selfDeploy();

			GammaCorrectionUniformInterface &gammaCorrectionUI = __gammaCorrectionUB.getInterface();
			gammaCorrectionUI.gamma = __gamma;
			__gammaCorrectionUB.selfDeploy();
		});
	}

	void GammaCorrectionPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__setupTransaction();
		ForwardPostProcessor::render(renderTarget);
	}
}