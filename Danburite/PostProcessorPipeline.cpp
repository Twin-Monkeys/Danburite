#include "PostProcessorPipeline.h"
#include "PhongCalcMethodType.h"
#include "TranslucencySwitchType.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PostProcessorPipeline::PostProcessorPipeline() noexcept
	{
		__pWboitFrameBuffer->setOutputColorBuffers(
			{
				ColorBufferType::COLOR_ATTACHMENT0,
				ColorBufferType::COLOR_ATTACHMENT1
			});

		__opaqueSetup.setup([this](ContextStateManager &stateMgr)
		{
			__translucencySwitcherUB.getInterface().mode = GLuint(TranslucencySwitchType::OPAQUE_MODE);
			__translucencySwitcherUB.selfDeploy();
		});

		__translucentSetup.setup([this](ContextStateManager &stateMgr)
		{
			__phongUB.getInterface().calcMethodType = GLuint(PhongCalcMethodType::FORWARD);
			__phongUB.selfDeploy();

			__translucencySwitcherUB.getInterface().mode = GLuint(TranslucencySwitchType::TRANSLUCENCY_MODE);
			__translucencySwitcherUB.selfDeploy();

			stateMgr.setState(GLStateType::DEPTH_TEST, true);
			stateMgr.setState(GLStateType::STENCIL_TEST, false);
			stateMgr.setState(GLStateType::BLEND, true);
			stateMgr.setState(GLStateType::CULL_FACE, false);

			stateMgr.enableDepthMask(false);
			stateMgr.setDepthFunction(DepthStencilFunctionType::LESS);

			stateMgr.setBlendingEquation(BlendingEquationType::ADD);
			stateMgr.setBlendingFunction(0, BlendingFunctionType::ONE, BlendingFunctionType::ONE);
			stateMgr.setBlendingFunction(1, BlendingFunctionType::ZERO, BlendingFunctionType::ONE_MINUS_SRC_COLOR);
		});

		__compositionSetup.setup([this](ContextStateManager &stateMgr)
		{
			TextureContainerUniformInterface &textureUI = __texContainerUB.getInterface();
			textureUI.textures = { 0ULL, __pWboitAccumAttachment->getHandle() };
			textureUI.textures = { 1ULL, __pWboitRevealageAttachment->getHandle() };

			__texContainerUB.selfDeploy();

			stateMgr.setState(GLStateType::DEPTH_TEST, false);
			stateMgr.setState(GLStateType::STENCIL_TEST, false);
			stateMgr.setState(GLStateType::BLEND, true);
			stateMgr.setState(GLStateType::CULL_FACE, true);

			stateMgr.setCulledFace(FacetType::BACK);
			stateMgr.setFrontFace(WindingOrderType::COUNTER_CLOCKWISE);

			stateMgr.setBlendingEquation(BlendingEquationType::ADD);
			stateMgr.setBlendingFunction(BlendingFunctionType::SRC_ALPHA, BlendingFunctionType::ONE_MINUS_SRC_ALPHA);
		});
	}

	FrameBuffer &PostProcessorPipeline::getFrameBuffer() noexcept
	{
		if (__pipeline.empty())
			return *__pRenderTarget;

		return __pipeline[0]->getFrameBuffer();
	}

	const FrameBuffer &PostProcessorPipeline::getFrameBuffer() const noexcept
	{
		if (__pipeline.empty())
			return *__pRenderTarget;

		return __pipeline[0]->getFrameBuffer();
	}

	void PostProcessorPipeline::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__screenSize = { width, height };

		__pWboitAccumAttachment = __attachmentServerPingPong[1].getTexRectangle(
			width, height, TextureInternalFormatType::RGBA32F, TextureExternalFormatType::RGBA,
			TextureDataType::FLOAT, TextureMinFilterValue::LINEAR, TextureMagFilterValue::LINEAR);

		__pWboitRevealageAttachment = __attachmentServerPingPong[1].getTexRectangle(
			width, height, TextureInternalFormatType::R16F, TextureExternalFormatType::RED,
			TextureDataType::FLOAT, TextureMinFilterValue::LINEAR, TextureMagFilterValue::LINEAR);

		__pWboitDepthStencilAttachment = __attachmentServerPingPong[1].getRenderBuffer(
			width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

		__pWboitFrameBuffer->attach(AttachmentType::COLOR_ATTACHMENT0, *__pWboitAccumAttachment);
		__pWboitFrameBuffer->attach(AttachmentType::COLOR_ATTACHMENT1, *__pWboitRevealageAttachment);
		__pWboitFrameBuffer->attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pWboitDepthStencilAttachment);

		for (const unique_ptr<PostProcessor> &pProcessor : __pipeline)
			pProcessor->setScreenSize(width, height);
	}

	void PostProcessorPipeline::render(
		const SetupTransaction &sceneDrawingSetup,
		BatchProcessor<SceneObject> &drawer, Skybox *const pSkybox, const FrameBufferBlitFlag bufferClearFlag) noexcept
	{
		PostProcessor *pCurProcessor = nullptr;
		PostProcessor *pNextProcessor = nullptr;
		FrameBuffer *pFirstFrameBuffer = nullptr;

		if (__pipeline.empty())
			pFirstFrameBuffer = __pRenderTarget;
		else
		{
			pCurProcessor = __pipeline[0].get();
			pFirstFrameBuffer = &(pCurProcessor->getFrameBuffer());
		}


		// Draw opaque
		sceneDrawingSetup();
		__opaqueSetup();

		pFirstFrameBuffer->clearBuffers(bufferClearFlag);
		drawer.process([](SceneObject& iter)
		{
			iter.drawUnderMaterialCondition(false, &Material::isTranslucencyEnabled);
		});

		if (pSkybox)
			pSkybox->draw();


		// Draw translucent
		pFirstFrameBuffer->blit(*__pWboitFrameBuffer, FrameBufferBlitFlag::DEPTH, __screenSize.x, __screenSize.y);
		__pWboitFrameBuffer->clearColorBuffer(0, 0.f);
		__pWboitFrameBuffer->clearColorBuffer(1, 1.f);

		__translucentSetup();
		drawer.process([](SceneObject& iter)
		{
			iter.drawUnderMaterialCondition(true, &Material::isTranslucencyEnabled);
		});


		// Wboit composition
		__compositionSetup();
		pFirstFrameBuffer->bind();
		__wboitProgram.bind();
		__fullscreenDrawer.draw();


		for (size_t i = 1ULL; i < __pipeline.size(); i++)
		{
			pNextProcessor = __pipeline[i].get();

			pCurProcessor->render(pNextProcessor->getFrameBuffer());
			pCurProcessor = pNextProcessor;
		}

		if (pCurProcessor)
			pCurProcessor->render(*__pRenderTarget);
	}
}