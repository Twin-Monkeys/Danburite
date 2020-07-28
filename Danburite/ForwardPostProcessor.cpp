#include "ForwardPostProcessor.h"
#include "ProgramFactory.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ForwardPostProcessor::ForwardPostProcessor(Program &program, const bool attachDepthBuffer) :
		__program(program), __attachDepthBuffer(attachDepthBuffer)
	{}

	ForwardPostProcessor::ForwardPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_FORWARD), attachDepthBuffer)
	{}

	void ForwardPostProcessor::_onRender(
		PostProcessor* const pBoundProcessor,
		UniformBuffer &texContainerSetter, FullscreenDrawer &fullscreenDrawer) noexcept
	{
		texContainerSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::TEX0, __pColorAttachment->getHandle());

		__program.bind();
		fullscreenDrawer.draw();
	}

	void ForwardPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__pColorAttachment = _getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);

		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pColorAttachment);

		if (__attachDepthBuffer)
		{
			__pDepthStencilAttachment =
				_getRenderBuffer(width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

			_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
		}
	}
}