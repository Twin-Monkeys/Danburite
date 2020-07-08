#include "MSAAPostProcessor.h"
#include "ShaderIdentifier.h"
#include "ProgramFactory.h"
#include "TextureUtil.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	MSAAPostProcessor::MSAAPostProcessor(const GLsizei numSamplePoints, const bool fixedSampleLocations) :
		__program(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_MSAA)),
		NUM_SAMPLE_POINTS(numSamplePoints),
		FIXED_SAMPLE_LOCATIONS(fixedSampleLocations),
		__pColorAttachment(make_unique<TextureMultisample>()),
		__pDepthStencilAttachment(make_unique<RenderBufferMultisample>())
	{
		assert(NUM_SAMPLE_POINTS);
	}

	void MSAAPostProcessor::_onRender(UniformBuffer &attachmentSetter, VertexArray &fullscreenQuadVA) noexcept
	{
		// AMD Bug; Cannot use bindless sampler2DMS
		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT0, TextureUtil::getHandleIfExist(__pColorAttachment));

		__program.bind();
		fullscreenQuadVA.draw();
	}

	void MSAAPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__pColorAttachment->memoryAlloc(
			width, height, TextureInternalFormatType::RGB16F, NUM_SAMPLE_POINTS, FIXED_SAMPLE_LOCATIONS);

		__pDepthStencilAttachment->memoryAlloc(
			width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8, NUM_SAMPLE_POINTS);

		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pColorAttachment);
		_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
	}
}