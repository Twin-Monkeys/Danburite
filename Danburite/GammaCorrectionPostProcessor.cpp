#include "GammaCorrectionPostProcessor.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"
#include "Material.h"

using namespace ObjectGL;

namespace Danburite
{
	GammaCorrectionPostProcessor::GammaCorrectionPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_GAMMA_CORRECTION), attachDepthBuffer),

		__gammaCorrectionSetter(
			UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::GAMMA_CORRECTION))
	{
		__setupTransaction.setSetupFunction([this](ContextStateManager& stateMgr)
		{
			__gammaCorrectionSetter.setUniformFloat(
				ShaderIdentifier::Name::GammaCorrection::GAMMA, __gamma);
		});

		setGamma(Constant::GammaCorrection::DEFAULT_GAMMA);
	}

	void GammaCorrectionPostProcessor::setGamma(const float gamma) noexcept
	{
		__gamma = gamma;
		Material::setGamma(gamma);
	}

	void GammaCorrectionPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__setupTransaction.setup();
		ForwardPostProcessor::render(renderTarget);
	}
}