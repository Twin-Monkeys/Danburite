#include "PostProcessorPipeline.h"
#include "PhongCalcMethodType.h"
#include "TranslucencySwitchType.h"

using namespace std;
using namespace ObjectGL;

namespace Danburite
{
	PostProcessorPipeline::PostProcessorPipeline() noexcept
	{
		__opaqueSetup.setSetupFunction([this](ContextStateManager &stateMgr)
		{
			__translucencySwitcherSetter.setUniformUint(
				ShaderIdentifier::Name::TranslucencySwitcher::MODE, GLuint(TranslucencySwitchType::OPAQUE_MODE));
		});

		__translucentSetup.setSetupFunction([this](ContextStateManager &stateMgr)
		{
			__phongSetter.setUniformUint(
				ShaderIdentifier::Name::Phong::CALC_METHOD_TYPE, GLuint(PhongCalcMethodType::FORWARD));

			__translucencySwitcherSetter.setUniformUint(
				ShaderIdentifier::Name::TranslucencySwitcher::MODE, GLuint(TranslucencySwitchType::TRANSLUCENCY_MODE));

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

		__compositionSetup.setSetupFunction([this](ContextStateManager &stateMgr)
		{
			__texContainerSetter.setUniformUvec2(
				ShaderIdentifier::Name::Attachment::TEX0, __pWboitAccumAttachment->getHandle());

			__texContainerSetter.setUniformUvec2(
				ShaderIdentifier::Name::Attachment::TEX1, __pWboitRevealageAttachment->getHandle());

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
			width, height, TextureInternalFormatType::RGBA16F, TextureExternalFormatType::RGBA,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);

		__pWboitRevealageAttachment = __attachmentServerPingPong[1].getTexRectangle(
			width, height, TextureInternalFormatType::R16F, TextureExternalFormatType::RED,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST);

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
		BatchProcessor<SceneObject> &drawer, Skybox &skybox, const FrameBufferBlitFlag bufferClearFlag) noexcept
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
		sceneDrawingSetup.setup();
		__opaqueSetup.setup();

		pFirstFrameBuffer->clearBuffers(bufferClearFlag);
		drawer.process([](SceneObject& iter)
		{
			iter.drawUnderMaterialCondition(false, &Material::isTranslucencyEnabled);
		});

		skybox.draw();


		// Draw translucent
		pFirstFrameBuffer->blit(*__pWboitFrameBuffer, FrameBufferBlitFlag::DEPTH, __screenSize.x, __screenSize.y);
		__pWboitFrameBuffer->clearColorBuffer(0, 0.f);
		__pWboitFrameBuffer->clearColorBuffer(1, 1.f);

		__translucentSetup.setup();
		drawer.process([](SceneObject& iter)
		{
			iter.drawUnderMaterialCondition(true, &Material::isTranslucencyEnabled);
		});


		// Wboit composition
		__compositionSetup.setup();
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