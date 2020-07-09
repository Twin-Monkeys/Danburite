#include "ForwardPostProcessor.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ForwardPostProcessor::ForwardPostProcessor(Program &program, const bool attachDepthBuffer) :
		__program(program)
	{
		__initColorAttachment();

		if (attachDepthBuffer)
			__pDepthStencilAttachment = make_unique<RenderBuffer>();
	}

	ForwardPostProcessor::ForwardPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_FORWARD), attachDepthBuffer)
	{}

	void ForwardPostProcessor::__initColorAttachment() noexcept
	{
		__pColorAttachment = make_unique<AttachableTexture2D>();
		__pColorAttachment->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		__pColorAttachment->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		__pColorAttachment->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pColorAttachment->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	}

	void ForwardPostProcessor::_onRender(UniformBuffer &attachmentSetter, VertexArray &fullscreenQuadVA) noexcept
	{
		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT0,
			TextureUtil::getHandleIfExist(__pColorAttachment));

		__program.bind();
		fullscreenQuadVA.draw();
	}

	void ForwardPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		if (__pColorAttachment->isHandleCreated())
			__initColorAttachment();

		__pColorAttachment->memoryAlloc(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB);

		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pColorAttachment);

		if (__pDepthStencilAttachment)
		{
			__pDepthStencilAttachment->memoryAlloc(
				width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

			_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
		}
	}
}