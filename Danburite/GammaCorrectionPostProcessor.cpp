#include "GammaCorrectionPostProcessor.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"

using namespace ObjectGL;

namespace Danburite
{
	GammaCorrectionPostProcessor::GammaCorrectionPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_GAMMA_CORRECTION), attachDepthBuffer),

		__gammaCorrectionSetter(
			UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::GAMMA_CORRECTION))
	{}

	void GammaCorrectionPostProcessor::_onRender(UniformBuffer &attachmentSetter, VertexArray &fullscreenQuadVA) noexcept
	{
		__gammaCorrectionSetter.setUniformFloat(ShaderIdentifier::Name::GammaCorrection::GAMMA, __gamma);
		ForwardPostProcessor::_onRender(attachmentSetter, fullscreenQuadVA);
	}
}