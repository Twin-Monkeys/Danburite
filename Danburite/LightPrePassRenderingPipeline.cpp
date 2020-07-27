#include "LightPrePassRenderingPipeline.h"
#include "GLFunctionWrapper.h"
#include "UniformBufferFactory.h"
#include "ProgramFactory.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	LightPrePassRenderingPipeline::LightPrePassRenderingPipeline(
		LightHandler& lightHandler, PerspectiveCamera& camera,
		Drawer& drawer, PostProcessingPipeline& ppPipeline) :
		RenderingPipeline(lightHandler, camera, drawer, ppPipeline),
		__texContainerSetter(UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::TEX_CONTAINER)),
		__pNormalShininessFB(make_unique<FrameBuffer>()),
		__pLightingFB(make_unique<FrameBuffer>()),
		__geometryProgram(ProgramFactory::getInstance().getProgram(ProgramType::LIGHT_PREPASS_GEOMETRY_EXTRACTION)),
		__lightingProgram(ProgramFactory::getInstance().getProgram(ProgramType::LIGHT_PREPASS_LIGHTING))
	{
		__pNormalShininessFB->setOutputColorBuffers(
			{ ColorBufferType::COLOR_ATTACHMENT0, ColorBufferType::COLOR_ATTACHMENT1 });

		__pLightingFB->setOutputColorBuffers(
			{
				ColorBufferType::COLOR_ATTACHMENT0,
				ColorBufferType::COLOR_ATTACHMENT1,
				ColorBufferType::COLOR_ATTACHMENT2
			});
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
		__pAmbientAttenuationAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGBA16F, TextureExternalFormatType::RGBA,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 0);

		__pDiffuseOcclusionInvAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGBA16F, TextureExternalFormatType::RGBA,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 1);

		__pSpecularAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);

		__pLightingFB->attach(AttachmentType::COLOR_ATTACHMENT0, *__pAmbientAttenuationAttachment);
		__pLightingFB->attach(AttachmentType::COLOR_ATTACHMENT1, *__pDiffuseOcclusionInvAttachment);
		__pLightingFB->attach(AttachmentType::COLOR_ATTACHMENT2, *__pSpecularAttachment);
	}

	void LightPrePassRenderingPipeline::render() noexcept
	{
		_lightHandler.batchBakeDepthMap(_drawer);
		_lightHandler.batchDeploy();

		_cameraSetter.directDeploy(_camera);

		// Geometry pass
		__pNormalShininessFB->bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
		__geometryProgram.bind();
		_drawer.batchRawDrawcall();


		// Lighting pass
		__pLightingFB->bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR);

		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, false);
		GLFunctionWrapper::setCulledFace(FacetType::FRONT);

		__lightingProgram.bind();
		_lightHandler.batchVolumeDrawcall();


		FrameBuffer::unbind();

		__pNormalShininessFB->blit(
			nullptr, 
			FrameBufferBlitFlag::COLOR_DEPTH_STENCIL, 0, 0, 1600, 900, 0, 0, 1600, 900);
	}
}