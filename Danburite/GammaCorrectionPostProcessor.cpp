#include "GammaCorrectionPostProcessor.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "Material.h"
#include "Constant.h"

using namespace ObjectGL;

namespace Danburite
{
	GammaCorrectionPostProcessor::GammaCorrectionPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_GAMMA_CORRECTION), attachDepthBuffer)
	{
		__setupTransaction.setSetupFunction([this](ContextStateManager& stateMgr)
		{
			__materialSetter.setUniformFloat(
				ShaderIdentifier::Name::Material::GAMMA, __gamma);

			__gammaCorrectionSetter.setUniformFloat(
				ShaderIdentifier::Name::GammaCorrection::GAMMA, __gamma);
		});

		setGamma(Constant::GammaCorrection::DEFAULT_GAMMA);
	}

	void GammaCorrectionPostProcessor::setGamma(const float gamma) noexcept
	{
		__gamma = gamma;
	}

	void GammaCorrectionPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__setupTransaction.setup();
		ForwardPostProcessor::render(renderTarget);
	}
}