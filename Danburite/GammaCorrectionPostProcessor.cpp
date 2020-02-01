#include "GammaCorrectionPostProcessor.h"
#include "ShaderIdentifier.h"

using namespace ObjectGL;

namespace Danburite
{
	GammaCorrectionPostProcessor::GammaCorrectionPostProcessor(UniformSetter &parameterSetter) :
		ForwardPostProcessor(ProgramType::POST_PROCESS_GAMMA_CORRECTION),
		__paramSetter(parameterSetter)
	{}

	void GammaCorrectionPostProcessor::_onRender() noexcept
	{
		ForwardPostProcessor::_onRender();
		__paramSetter.setUniformFloat(ShaderIdentifier::Name::GammaCorrection::GAMMA, __gamma);
	}

	void GammaCorrectionPostProcessor::setGamma(const GLfloat gamma) noexcept
	{
		__gamma = gamma;
	}
}