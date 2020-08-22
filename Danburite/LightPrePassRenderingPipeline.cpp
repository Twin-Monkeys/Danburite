#include "LightPrePassRenderingPipeline.h"
#include "PhongCalcMethodType.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	LightPrePassRenderingPipeline::LightPrePassRenderingPipeline(
		LightManager& lightManager, PerspectiveCamera& camera, BatchProcessor<SceneObject>& drawer, Skybox& skybox) :
		RenderingPipeline(lightManager, camera, drawer, skybox)
	{
		__pNormalShininessFB->setOutputColorBuffers(
			{ ColorBufferType::COLOR_ATTACHMENT0, ColorBufferType::COLOR_ATTACHMENT1 });

		__pLightingFB->setOutputColorBuffers(
			{
				ColorBufferType::COLOR_ATTACHMENT0,
				ColorBufferType::COLOR_ATTACHMENT1,
				ColorBufferType::COLOR_ATTACHMENT2
			});

		__geometryPassSetup.setup([this](ContextStateManager &stateMgr)
		{
			stateMgr.setState(GLStateType::DEPTH_TEST, true);
			stateMgr.setState(GLStateType::STENCIL_TEST, true);
			stateMgr.setState(GLStateType::CULL_FACE, true);
			stateMgr.setState(GLStateType::BLEND, false);

			stateMgr.setDepthFunction(DepthStencilFunctionType::LESS);
			stateMgr.enableDepthMask(true);

			stateMgr.setStencilMask(0xFFU);
			stateMgr.setStencilFunction(DepthStencilFunctionType::ALWAYS, 0x01U);
			stateMgr.setStencilOperation(
				StencilOperationType::KEEP, StencilOperationType::KEEP, StencilOperationType::REPLACE);

			stateMgr.setCulledFace(FacetType::BACK);
			stateMgr.setFrontFace(WindingOrderType::COUNTER_CLOCKWISE);
		});

		__lightingPassSetup.setup([this](ContextStateManager &stateMgr)
		{
			__texContainerSetter.setUniformUvec2(
				ShaderIdentifier::Name::Attachment::TEX0, __pPosAttachment->getHandle());

			__texContainerSetter.setUniformUvec2(
				ShaderIdentifier::Name::Attachment::TEX1, __pNormalShininessAttachment->getHandle());

			stateMgr.setClearColor(0.f, 0.f, 0.f, 0.f);
			stateMgr.setState(GLStateType::DEPTH_TEST, false);
			stateMgr.setState(GLStateType::BLEND, true);

			stateMgr.setStencilFunction(DepthStencilFunctionType::EQUAL, 0x01U);
			stateMgr.setStencilMask(0x00U);
			stateMgr.setCulledFace(FacetType::FRONT);
			stateMgr.setBlendingFunction(BlendingFunctionType::ONE, BlendingFunctionType::ONE);
		});

		__compositionPassSetup.setup([this](ContextStateManager& stateMgr)
		{
			__phongSetter.setUniformUint(
				ShaderIdentifier::Name::Phong::CALC_METHOD_TYPE,
				GLuint(PhongCalcMethodType::LIGHT_PREPASS));

			__lightPrePassSetter.setUniformUvec2(
				ShaderIdentifier::Name::LightPrePass::LIGHT_AMBIENT_TEX,
				__pLightAmbientAttachment->getHandle());

			__lightPrePassSetter.setUniformUvec2(
				ShaderIdentifier::Name::LightPrePass::LIGHT_DIFFUSE_TEX,
				__pLightDiffuseAttachment->getHandle());

			__lightPrePassSetter.setUniformUvec2(
				ShaderIdentifier::Name::LightPrePass::LIGHT_SPECULAR_TEX,
				__pLightSpecularAttachment->getHandle());

			stateMgr.setState(GLStateType::DEPTH_TEST, true);
			stateMgr.setState(GLStateType::STENCIL_TEST, false);
			// stateMgr.setState(GLStateType::BLEND, false);
			// stateMgr.setState(GLStateType::CULL_FACE, true);

			// stateMgr.enableDepthMask(false);
			stateMgr.setDepthFunction(DepthStencilFunctionType::LEQUAL);
			stateMgr.setCulledFace(FacetType::BACK);
			// stateMgr.setFrontFace(WindingOrderType::COUNTER_CLOCKWISE);
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
		__pLightingFB->attach(AttachmentType::STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
	}

	void LightPrePassRenderingPipeline::_onRender(
		LightManager& lightManager, PerspectiveCamera& camera,
		BatchProcessor<SceneObject>& drawer, Skybox& skybox, PostProcessorPipeline& ppPipeline) noexcept
	{
		lightManager.process(&Light::bakeDepthMap, drawer);
		lightManager.selfDeploy();
		camera.selfDeploy();


		// Geometry pass
		__geometryPassSetup();
		__pNormalShininessFB->clearBuffers(FrameBufferBlitFlag::DEPTH | FrameBufferBlitFlag::STENCIL);
		__geometryProgram.bind();

		// drawer.process(&SceneObject::rawDrawcall);
		drawer.process([](SceneObject& iter)
		{
			iter.rawDrawcallUnderMaterialCondition(false, &Material::isTranslucencyEnabled);
		});


		// Lighting pass
		__lightingPassSetup();
		__pLightingFB->clearBuffers(FrameBufferBlitFlag::COLOR);
		__lightingProgram.bind();
		lightManager.process(&Light::volumeDrawcall);


		// Composition pass (ordinary forward rendering)
		const ivec2& screenSize = getScreenSize();
		__pNormalShininessFB->blit(
			ppPipeline.getFrameBuffer(), FrameBufferBlitFlag::DEPTH, screenSize.x, screenSize.y);

		ppPipeline.render(__compositionPassSetup, drawer, skybox, FrameBufferBlitFlag::COLOR);
	}
}