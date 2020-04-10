#include "GammaCorrectionPostProcessor.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"

using namespace ObjectGL;

namespace Danburite
{
	GammaCorrectionPostProcessor::GammaCorrectionPostProcessor() :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_GAMMA_CORRECTION)),

		__gammaCorrectionSetter(
			UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::GAMMA_CORRECTION))
	{}

	void GammaCorrectionPostProcessor::_onRender(UniformSetter &attachmentSetter, VertexArray &fullscreenQuadVA) noexcept
	{
		__gammaCorrectionSetter.setUniformFloat(ShaderIdentifier::Name::GammaCorrection::GAMMA, __gamma);
		ForwardPostProcessor::_onRender(attachmentSetter, fullscreenQuadVA);
	}

	void GammaCorrectionPostProcessor::setGamma(const float gamma) noexcept
	{
		__gamma = gamma;
		assert(__gamma > 0.f);
	}
}