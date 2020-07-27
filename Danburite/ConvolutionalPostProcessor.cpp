#include "ConvolutionalPostProcessor.h"
#include "UniformBufferFactory.h"
#include "ProgramFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	ConvolutionalPostProcessor::ConvolutionalPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_CONVOLUTIONAL), attachDepthBuffer),

		__convSetter(
			UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::CONVOLUTION))
	{}

	void ConvolutionalPostProcessor::setKernel(const GLfloat *const pData, const GLuint kernelSize) noexcept
	{
		__kernelSize = kernelSize;
		memcpy(__kernel.data(), pData, sizeof(GLfloat) * (kernelSize * kernelSize));
	}

	void ConvolutionalPostProcessor::_onRender(
		PostProcessor* const pBoundProcessor,
		UniformBuffer &attachmentSetter, FullscreenDrawer &fullscreenDrawer) noexcept
	{
		__convSetter.setUniformUint(
			ShaderIdentifier::Name::Convolutional::KERNEL_SIZE, __kernelSize);

		__convSetter.setUniformFloatArray(
			ShaderIdentifier::Name::Convolutional::KERNEL, __kernel.data(), __kernelSize * __kernelSize);

		ForwardPostProcessor::_onRender(pBoundProcessor, attachmentSetter, fullscreenDrawer);
	}
}