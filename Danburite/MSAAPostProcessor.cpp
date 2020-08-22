#include "MSAAPostProcessor.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	MSAAPostProcessor::MSAAPostProcessor(
		const bool attachDepthBuffer, const GLsizei numSamplePoints, const bool fixedSampleLocations) :
		__attachDepthBuffer(attachDepthBuffer),
		__NUM_SAMPLE_POINTS(numSamplePoints), __FIXED_SAMPLE_LOCATIONS(fixedSampleLocations)
	{
		assert(__NUM_SAMPLE_POINTS);

		__setupTransaction.setup([this](ContextStateManager& stateMgr)
		{
			// AMD Bug; Cannot use bindless sampler2DMS
			__texContainerSetter.setUniformUvec2(
				ShaderIdentifier::Name::Attachment::TEX0, __pColorAttachment->getHandle());

			stateMgr.setState(GLStateType::DEPTH_TEST, false);
			stateMgr.setState(GLStateType::STENCIL_TEST, false);
			stateMgr.setState(GLStateType::BLEND, false);
			stateMgr.setState(GLStateType::CULL_FACE, true);

			stateMgr.setCulledFace(FacetType::BACK);
			stateMgr.setFrontFace(WindingOrderType::COUNTER_CLOCKWISE);
		});
	}

	void MSAAPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__setupTransaction();
		renderTarget.bind();
		__program.bind();
		__fullscreenDrawer.draw();
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