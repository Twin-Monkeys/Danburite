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
		__setupTransaction.setup([this](ContextStateManager &stateMgr)
		{
			ConvolutionUniformInterface &convUniformInterface = __convUB.getInterface();

			convUniformInterface.kernelSize = __kernelSize;
			convUniformInterface.kernel =
				{ 0ULL, size_t { __kernelSize } * size_t { __kernelSize }, __kernel.data() };

			__convUB.selfDeploy();
		});
	}

	void ConvolutionalPostProcessor::setKernel(const GLfloat *const pData, const GLuint kernelSize) noexcept
	{
		__kernelSize = kernelSize;
		memcpy(__kernel.data(), pData, sizeof(GLfloat) * size_t { kernelSize } * size_t { kernelSize });
	}

	void ConvolutionalPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__setupTransaction();
		ForwardPostProcessor::render(renderTarget);
	}
}