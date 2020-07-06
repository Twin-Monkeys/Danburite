#include "ForwardPostProcessor.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ForwardPostProcessor::ForwardPostProcessor(Program &program) :
		__program(program),
		__pColorAttachment(make_unique<AttachableTexture2D>()),
		__pDepthStencilAttachment(make_unique<RenderBuffer>())
	{
		__pColorAttachment->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		__pColorAttachment->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		__pColorAttachment->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pColorAttachment->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	}

	ForwardPostProcessor::ForwardPostProcessor() :
		ForwardPostProcessor(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_FORWARD))
	{}

	void ForwardPostProcessor::_onRender(UniformBuffer &attachmentSetter, VertexArray &fullscreenQuadVA) noexcept
	{
		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT_ARRAY[0], TextureUtil::getHandleIfExist(__pColorAttachment));

		__program.bind();
		fullscreenQuadVA.draw();
	}

	void ForwardPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__pColorAttachment->memoryAlloc(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB);

		__pDepthStencilAttachment->memoryAlloc(
			width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pColorAttachment);
		_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
	}
}