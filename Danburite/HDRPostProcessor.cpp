#include "HDRPostProcessor.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"

using namespace ObjectGL;

namespace Danburite
{
	HDRPostProcessor::HDRPostProcessor() :
		ForwardPostProcessor(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_HDR)),

		__hdrSetter(
			UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::HDR))
	{}

	void HDRPostProcessor::_onRender(UniformBuffer &attachmentSetter, VertexArray &fullscreenQuadVA) noexcept
	{
		__hdrSetter.setUniformFloat(ShaderIdentifier::Name::HDR::EXPOSURE, __exposure);
		ForwardPostProcessor::_onRender(attachmentSetter, fullscreenQuadVA);
	}
}