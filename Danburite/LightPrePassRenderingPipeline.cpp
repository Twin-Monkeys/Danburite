#include "LightPrePassRenderingPipeline.h"
#include "GLFunctionWrapper.h"
#include "UniformBufferFactory.h"
#include "ProgramFactory.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	LightPrePassRenderingPipeline::LightPrePassRenderingPipeline(
		LightManager &lightManager, PerspectiveCamera& camera,
		BatchProcessor<Drawable> &drawer, PostProcessingPipeline& ppPipeline) :
		RenderingPipeline(RenderingPipelineType::LIGHT_PREPASS, lightManager, camera, drawer, ppPipeline),
		__texContainerSetter(UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::TEX_CONTAINER)),
		__lightPrePassSetter(UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::LIGHT_PREPASS)),
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

	void LightPrePassRenderingPipeline::_onSetScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		// pNormalShininessFB
		__pPosAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGB32F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);

		__pNormalShininessAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGBA32F, TextureExternalFormatType::RGBA,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);

		__pDepthStencilAttachment = __attachmentServer.getRenderBuffer(
			width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

		__pNormalShininessFB->attach(AttachmentType::COLOR_ATTACHMENT0, *__pPosAttachment);
		__pNormalShininessFB->attach(AttachmentType::COLOR_ATTACHMENT1, *__pNormalShininessAttachment);
		__pNormalShininessFB->attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);


		// pLightingFB
		__pLightAmbientAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 0);

		__pLightDiffuseAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 1);

		__pLightSpecularAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 2);

		__pLightingFB->attach(AttachmentType::COLOR_ATTACHMENT0, *__pLightAmbientAttachment);
		__pLightingFB->attach(AttachmentType::COLOR_ATTACHMENT1, *__pLightDiffuseAttachment);
		__pLightingFB->attach(AttachmentType::COLOR_ATTACHMENT2, *__pLightSpecularAttachment);
	}

	void LightPrePassRenderingPipeline::_onRender(
		LightManager &lightManager, PerspectiveCamera &camera,
		BatchProcessor<Drawable> &drawer, PostProcessingPipeline &ppPipeline) noexcept
	{
		lightManager.process(&Light::bakeDepthMap, drawer);
		lightManager.selfDeploy();

		camera.selfDeploy();


		// Geometry pass
		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);

		__pNormalShininessFB->bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR_DEPTH);

		__geometryProgram.bind();
		drawer.process(&Drawable::rawDrawcall);


		// Lighting pass
		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, false);
		GLFunctionWrapper::setOption(GLOptionType::BLEND, true);
		GLFunctionWrapper::setBlendingFunction(BlendingFunctionType::ONE, BlendingFunctionType::ONE);
		GLFunctionWrapper::setCulledFace(FacetType::FRONT);

		__pLightingFB->bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR);

		__texContainerSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::TEX0, __pPosAttachment->getHandle());

		__texContainerSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::TEX1, __pNormalShininessAttachment->getHandle());

		__lightingProgram.bind();
		lightManager.process(&Light::volumeDrawcall);


		// Composition pass (ordinary forward rendering)
		__lightPrePassSetter.setUniformUvec2(
			ShaderIdentifier::Name::LightPrePass::LIGHT_AMBIENT_TEX,
			__pLightAmbientAttachment->getHandle());

		__lightPrePassSetter.setUniformUvec2(
			ShaderIdentifier::Name::LightPrePass::LIGHT_DIFFUSE_TEX,
			__pLightDiffuseAttachment->getHandle());

		__lightPrePassSetter.setUniformUvec2(
			ShaderIdentifier::Name::LightPrePass::LIGHT_SPECULAR_TEX,
			__pLightSpecularAttachment->getHandle());

		GLFunctionWrapper::setOption(GLOptionType::DEPTH_TEST, true);
		GLFunctionWrapper::setDepthFunction(DepthStencilFunctionType::LEQUAL);
		GLFunctionWrapper::setOption(GLOptionType::BLEND, false);
		GLFunctionWrapper::setCulledFace(FacetType::BACK);

		FrameBuffer &firstFB = ppPipeline.getProcessor(0).getFrameBuffer();
		const ivec2 &screenSize = getScreenSize();

		__pNormalShininessFB->blit(
			&firstFB, FrameBufferBlitFlag::DEPTH,
			0, 0, screenSize.x, screenSize.y, 0, 0, screenSize.x, screenSize.y);

		ppPipeline.bind();
		GLFunctionWrapper::clearBuffers(FrameBufferBlitFlag::COLOR);

		drawer.process(&Drawable::draw);
		PostProcessingPipeline::unbind();

		ppPipeline.render();
	}
}