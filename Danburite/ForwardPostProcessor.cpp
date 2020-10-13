#include "ForwardPostProcessor.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	ForwardPostProcessor::ForwardPostProcessor(Program &program, const bool attachDepthBuffer) :
		__program(program), __attachDepthBuffer(attachDepthBuffer)
	{
		__setupTransaction.setup([this] (ContextStateManager &stateMgr)
		{
			__texContainerUB.getInterface().textures = { 0, __pColorAttachment->getHandle() };
			__texContainerUB.selfDeploy();

			stateMgr.setState(GLStateType::DEPTH_TEST, false);
			stateMgr.setState(GLStateType::STENCIL_TEST, false);
			stateMgr.setState(GLStateType::BLEND, false);
			stateMgr.setState(GLStateType::CULL_FACE, true);

			stateMgr.setCulledFace(FacetType::BACK);
			stateMgr.setFrontFace(WindingOrderType::COUNTER_CLOCKWISE);
		});
	}

	ForwardPostProcessor::ForwardPostProcessor(const bool attachDepthBuffer) :
		ForwardPostProcessor(ProgramFactory::getInstance().
			getProgram(ProgramType::POST_PROCESS_FORWARD), attachDepthBuffer)
	{}

	void ForwardPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__setupTransaction();
		renderTarget.bind();
		__program.bind();
		__fullscreenDrawer.draw();
	}

	void ForwardPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__pColorAttachment = _getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::LINEAR, TextureMagFilterValue::LINEAR);

		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pColorAttachment);

		if (__attachDepthBuffer)
		{
			__pDepthStencilAttachment =
				_getRenderBuffer(width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

			_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
		}
	}
}