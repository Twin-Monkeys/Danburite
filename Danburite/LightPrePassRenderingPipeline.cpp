#include "LightPrePassRenderingPipeline.h"
#include "PhongCalcMethodType.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	LightPrePassRenderingPipeline::LightPrePassRenderingPipeline(
		LightManager& lightManager, PerspectiveCamera& camera, BatchProcessor<SceneObject>& drawer, Skybox *const pSkybox) :
		RenderingPipeline(lightManager, camera, drawer, pSkybox)
	{
		__pPosNormalShininessFB->setOutputColorBuffers(
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

		__ssaoSetup.setup([this](ContextStateManager &stateMgr)
		{
			TextureContainerUniformInterface& texContainerUI = __texContainerUB.getInterface();
			texContainerUI.textures = { 0ULL, __pPosAttachment->getHandle() };
			texContainerUI.textures = { 1ULL, __pNormalShininessAttachment->getHandle() };

			__texContainerUB.selfDeploy();

			stateMgr.setState(GLStateType::DEPTH_TEST, false);
			stateMgr.setState(GLStateType::STENCIL_TEST, false);
			stateMgr.setState(GLStateType::BLEND, false);
		});

		__ssaoPPSetup.setup([this](ContextStateManager &stateMgr)
		{
			TextureContainerUniformInterface& texContainerUI = __texContainerUB.getInterface();
			texContainerUI.textures = { 0ULL, __pAOInvAttachment->getHandle() };
			__texContainerUB.selfDeploy();

			SSAOUniformInterface &ssaoUI = __ssaoUB.getInterface();
			ssaoUI.samplingRadius = __ssaoSamplingRadius;
			ssaoUI.strength = __ssaoStrength;
			ssaoUI.numSamples = __ssaoNumSamples;
			ssaoUI.blurRange = __ssaoBlurRange;
			__ssaoUB.selfDeploy();

			stateMgr.setState(GLStateType::DEPTH_TEST, false);
			stateMgr.setState(GLStateType::STENCIL_TEST, false);
			stateMgr.setState(GLStateType::BLEND, false);
		});

		__lightingPassSetup.setup([this](ContextStateManager &stateMgr)
		{
			TextureContainerUniformInterface& texContainerUI = __texContainerUB.getInterface();
			texContainerUI.textures = { 0ULL, __pPosAttachment->getHandle() };
			texContainerUI.textures = { 2ULL, __pAOInvPPAttachment->getHandle() };

			__texContainerUB.selfDeploy();

			stateMgr.setClearColor(0.f, 0.f, 0.f, 0.f);
			stateMgr.setState(GLStateType::DEPTH_TEST, false);
			stateMgr.setState(GLStateType::STENCIL_TEST, true);
			stateMgr.setState(GLStateType::BLEND, true);

			stateMgr.setStencilFunction(DepthStencilFunctionType::EQUAL, 0x01U);
			stateMgr.setStencilMask(0x00U);
			stateMgr.setBlendingFunction(BlendingFunctionType::ONE, BlendingFunctionType::ONE);
		});

		__compositionPassSetup.setup([this](ContextStateManager& stateMgr)
		{
			PhongUniformInterface &phongUI = __phongUB.getInterface();
			phongUI.calcMethodType = GLuint(PhongCalcMethodType::LIGHT_PREPASS);
			__phongUB.selfDeploy();

			LightPrePassUniformInterface &lightPrePassUI = __lightPrePassUB.getInterface();
			lightPrePassUI.ambientTex = __pLightAmbientAttachment->getHandle();
			lightPrePassUI.diffuseTex = __pLightDiffuseAttachment->getHandle();
			lightPrePassUI.specularTex = __pLightSpecularAttachment->getHandle();
			__lightPrePassUB.selfDeploy();

			stateMgr.setState(GLStateType::DEPTH_TEST, true);
			stateMgr.setState(GLStateType::STENCIL_TEST, false);
			stateMgr.setState(GLStateType::BLEND, false);
			stateMgr.setState(GLStateType::CULL_FACE, true);

			stateMgr.enableDepthMask(false);
			stateMgr.setDepthFunction(DepthStencilFunctionType::LEQUAL);
			stateMgr.setCulledFace(FacetType::BACK);
			stateMgr.setFrontFace(WindingOrderType::COUNTER_CLOCKWISE);
		});
	}

	void LightPrePassRenderingPipeline::_onSetScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		// pPosNormalShininessFB
		__pPosAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGB32F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);

		__pNormalShininessAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGBA32F, TextureExternalFormatType::RGBA,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);

		__pDepthStencilAttachment = __attachmentServer.getRenderBuffer(
			width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

		__pPosNormalShininessFB->attach(AttachmentType::COLOR_ATTACHMENT0, *__pPosAttachment);
		__pPosNormalShininessFB->attach(AttachmentType::COLOR_ATTACHMENT1, *__pNormalShininessAttachment);
		__pPosNormalShininessFB->attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);


		// pSSAOFB
		__pAOInvAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::R16F, TextureExternalFormatType::RED,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 0ULL);

		__pSSAOFB->attach(AttachmentType::COLOR_ATTACHMENT0, *__pAOInvAttachment);


		// pSSAOPPFB
		__pAOInvPPAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::R16F, TextureExternalFormatType::RED,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 1ULL);

		__pSSAOPPFB->attach(AttachmentType::COLOR_ATTACHMENT0, *__pAOInvPPAttachment);


		// pLightingFB
		__pLightAmbientAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 0ULL);

		__pLightDiffuseAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 1ULL);

		__pLightSpecularAttachment = __attachmentServer.getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 2ULL);

		__pLightingFB->attach(AttachmentType::COLOR_ATTACHMENT0, *__pLightAmbientAttachment);
		__pLightingFB->attach(AttachmentType::COLOR_ATTACHMENT1, *__pLightDiffuseAttachment);
		__pLightingFB->attach(AttachmentType::COLOR_ATTACHMENT2, *__pLightSpecularAttachment);
		__pLightingFB->attach(AttachmentType::STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
	}

	void LightPrePassRenderingPipeline::_onRender(
		LightManager& lightManager, PerspectiveCamera& camera,
		BatchProcessor<SceneObject>& drawer, Skybox *const pSkybox, PostProcessorPipeline& ppPipeline) noexcept
	{
		lightManager.process(&Light::bakeDepthMap, drawer);
		lightManager.selfDeploy();
		camera.selfDeploy();


		// Geometry pass
		__geometryPassSetup();

		#ifdef max
		#undef max
		__pPosNormalShininessFB->clearColorBuffer(0U, numeric_limits<float>::max());
		#endif
		__pPosNormalShininessFB->clearColorBuffer(1U, { 0.f, 1.f, 0.f, 0.f });
		__pPosNormalShininessFB->clearBuffers(FrameBufferBlitFlag::DEPTH | FrameBufferBlitFlag::STENCIL);
		__geometryProgram.bind();

		drawer.process([](SceneObject& iter)
		{
			iter.rawDrawcallUnderMaterialCondition(false, &Material::isTranslucencyEnabled);
		});


		// SSAO
		__ssaoSetup();
		__pSSAOFB->bind();
		__ssaoProgram.bind();
		__fullscreenDrawer.draw();


		// SSAO PP
		__ssaoPPSetup();
		__pSSAOPPFB->bind();
		__ssaoBlurProgram.bind();
		__fullscreenDrawer.draw();


		// Lighting pass
		__lightingPassSetup();
		__pLightingFB->clearBuffers(FrameBufferBlitFlag::COLOR);
		__lightingProgram.bind();
		lightManager.process(&Light::volumeDrawcall);


		// Composition pass (ordinary forward rendering)
		const ivec2& screenSize = getScreenSize();
		__pPosNormalShininessFB->blit(
			ppPipeline.getFrameBuffer(), FrameBufferBlitFlag::DEPTH, screenSize.x, screenSize.y);

		ppPipeline.render(__compositionPassSetup, drawer, pSkybox, FrameBufferBlitFlag::COLOR);
	}

	void LightPrePassRenderingPipeline::setSSAONumSamples(const GLuint numSamples)
	{
		if (numSamples > Constant::SSAO::MAX_NUM_SAMPLES)
			throw SSAOException("numSamples cannot over Constant::SSAO::MAX_NUM_SAMPLES.");

		__ssaoNumSamples = numSamples;
	}
}