#include "ConvolutionalPostProcessor.h"
#include "ProgramFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	ConvolutionalPostProcessor::ConvolutionalPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_CONVOLUTIONAL), attachDepthBuffer)
	{
		__setupTransaction.setSetupFunction([this](ContextStateManager &stateMgr)
		{
			__convSetter.setUniformUint(
				ShaderIdentifier::Name::Convolutional::KERNEL_SIZE, __kernelSize);

			__convSetter.setUniformFloatArray(
				ShaderIdentifier::Name::Convolutional::KERNEL, __kernel.data(), __kernelSize * __kernelSize);
		});
	}

	void ConvolutionalPostProcessor::setKernel(const GLfloat *const pData, const GLuint kernelSize) noexcept
	{
		__kernelSize = kernelSize;
		memcpy(__kernel.data(), pData, sizeof(GLfloat) * size_t(kernelSize) * size_t(kernelSize));
	}

	void ConvolutionalPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__setupTransaction.setup();
		ForwardPostProcessor::render(renderTarget);
	}
}