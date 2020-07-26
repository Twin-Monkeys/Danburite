#include "LightPrePassRenderingPipeline.h"
#include "GLFunctionWrapper.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	LightPrePassRenderingPipeline::LightPrePassRenderingPipeline(
		LightHandler& lightHandler, PerspectiveCamera& camera,
		Drawer& drawer, PostProcessingPipeline& ppPipeline) :
		RenderingPipeline(lightHandler, camera, drawer, ppPipeline),
		__pNormalShininessFB(make_unique<FrameBuffer>()),
		__extractionProgram(ProgramFactory::getInstance().
			getProgram(ProgramType::LIGHT_PREPASS_NORMAL_SHININESS_EXTRACTION))
	{}

	void LightPrePassRenderingPipeline::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		glViewport(0, 0, width, height);
		_camera.setAspectRatio(width, height);

		__pNormalSpecularAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGBA32F, TextureExternalFormatType::RGBA,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);

		__pDepthStencilAttachment = __attachmentServer.getRenderBuffer(
			width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

		__pNormalShininessFB->attach(
			AttachmentType::COLOR_ATTACHMENT0, *__pNormalSpecularAttachment);

		__pNormalShininessFB->attach(
			AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
	}

	void LightPrePassRenderingPipeline::render() noexcept
	{
		_lightHandler.batchDeploy();
		_cameraSetter.directDeploy(_camera);

		__pNormalShininessFB->bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

		__extractionProgram.bind();
		_drawer.batchRawDrawcall();
		FrameBuffer::unbind();

		__pNormalShininessFB->blit(
			nullptr, 
			FrameBufferBlitFlag::COLOR_DEPTH_STENCIL, 0, 0, 1600, 900, 0, 0, 1600, 900);
	}
}