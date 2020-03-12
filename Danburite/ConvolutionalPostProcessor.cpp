#include "ConvolutionalPostProcessor.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	ConvolutionalPostProcessor::ConvolutionalPostProcessor(UniformSetter &parameterSetter) :
		ForwardPostProcessor(ProgramType::POST_PROCESS_CONVOLUTIONAL), __paramSetter(parameterSetter)
	{}

	void ConvolutionalPostProcessor::setKernel(const GLfloat *const pData, const GLuint kernelSize) noexcept
	{
		__kernelSize = kernelSize;
		memcpy(__kernel.data(), pData, sizeof(GLfloat) * (kernelSize * kernelSize));
	}

	void ConvolutionalPostProcessor::_onRender() noexcept
	{
		ForwardPostProcessor::_onRender();

		__paramSetter.setUniformUint(
			ShaderIdentifier::Name::Convolutional::KERNEL_SIZE, __kernelSize);

		__paramSetter.setUniformFloatArray(
			ShaderIdentifier::Name::Convolutional::KERNEL, __kernel.data(), __kernelSize * __kernelSize);
	}
}