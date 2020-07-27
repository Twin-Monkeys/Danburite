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
			getProgram(ProgramType::LIGHT_PREPASS_GEOMETRY_EXTRACTION))
	{
		__pNormalShininessFB->setOutputColorBuffers(
			{ ColorBufferType::COLOR_ATTACHMENT0, ColorBufferType::COLOR_ATTACHMENT1 });
	}

	void LightPrePassRenderingPipeline::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		glViewport(0, 0, width, height);
		_camera.setAspectRatio(width, height);
		_ppPipeline.setScreenSize(width, height);

		// pNormalShininessFB
		__pPosAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGB32F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);

		__pNormalSpecularAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGBA32F, TextureExternalFormatType::RGBA,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);

		__pDepthStencilAttachment = __attachmentServer.getRenderBuffer(
			width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

		__pNormalShininessFB->attach(AttachmentType::COLOR_ATTACHMENT0, *__pPosAttachment);
		__pNormalShininessFB->attach(AttachmentType::COLOR_ATTACHMENT1, *__pNormalSpecularAttachment);
		__pNormalShininessFB->attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);

		// pLightingFB
		__pLightingAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGBA32F, TextureExternalFormatType::RGBA,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);
	}

	void LightPrePassRenderingPipeline::render() noexcept
	{
		_lightHandler.batchDeploy();
		_cameraSetter.directDeploy(_camera);

		__pNormalShininessFB->bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
		GLFunctionWrapper::setDepthMask(true);

		__extractionProgram.bind();
		_drawer.batchRawDrawcall();
		FrameBuffer::unbind();

		__pNormalShininessFB->blit(
			nullptr, 
			FrameBufferBlitFlag::COLOR_DEPTH_STENCIL, 0, 0, 1600, 900, 0, 0, 1600, 900);
	}
}