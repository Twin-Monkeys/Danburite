#include "MSAAPostProcessor.h"
#include "ShaderIdentifier.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	MSAAPostProcessor::MSAAPostProcessor(
		const bool attachDepthBuffer, const GLsizei numSamplePoints, const bool fixedSampleLocations) :
		__program(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_MSAA)),
		__attachDepthBuffer(attachDepthBuffer),
		__NUM_SAMPLE_POINTS(numSamplePoints),
		__FIXED_SAMPLE_LOCATIONS(fixedSampleLocations)
	{
		assert(__NUM_SAMPLE_POINTS);
	}

	void MSAAPostProcessor::_onRender(
		PostProcessor* const pBoundProcessor,
		UniformBuffer &texContainerSetter, FullscreenDrawer &fullscreenDrawer) noexcept
	{
		// AMD Bug; Cannot use bindless sampler2DMS
		texContainerSetter.setUniformUvec2(ShaderIdentifier::Name::Attachment::TEX0, __pColorAttachment->getHandle());

		__program.bind();
		fullscreenDrawer.draw();
	}

	void MSAAPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__pColorAttachment = _getTexMultisample(
			width, height, TextureInternalFormatType::RGB16F, __NUM_SAMPLE_POINTS, __FIXED_SAMPLE_LOCATIONS);

		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pColorAttachment);

		if (__attachDepthBuffer)
		{
			__pDepthStencilAttachment = _getRenderBufferMultisample(
				width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8, __NUM_SAMPLE_POINTS);

			_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
		}
	}
}