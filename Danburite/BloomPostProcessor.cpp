#include "BloomPostProcessor.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	BloomPostProcessor::BloomPostProcessor(const bool attachDepthBuffer) :
		__attachDepthBuffer(attachDepthBuffer)
	{
		__basicSetup.setup([this](ContextStateManager& stateMgr)
		{
			 BloomUniformInterface &bloomInterface = __bloomUB.getInterface();
			 bloomInterface.brightnessThreshold = __brightnessThreshold;
			 bloomInterface.effectStrength = __effectStrength;
			 __bloomUB.selfDeploy();

			stateMgr.setState(GLStateType::DEPTH_TEST, false);
			stateMgr.setState(GLStateType::STENCIL_TEST, false);
			stateMgr.setState(GLStateType::BLEND, false);
			stateMgr.setState(GLStateType::CULL_FACE, true);

			stateMgr.setCulledFace(FacetType::BACK);
			stateMgr.setFrontFace(WindingOrderType::COUNTER_CLOCKWISE);
		});

		__colorExtractionSetup.setup([this](ContextStateManager& stateMgr)
		{
			TextureContainerUniformInterface &texContainerInterface = __texContainerUB.getInterface();
			texContainerInterface.textures = { 0, __pOriginalColorAttachment->getHandle() };
			__texContainerUB.selfDeploy();
		});

		__horizBlurSetup.setup([this](ContextStateManager& stateMgr)
		{
			TextureContainerUniformInterface &texContainerInterface = __texContainerUB.getInterface();
			texContainerInterface.textures = { 0, __pBloomColorAttachment1->getHandle() };
			__texContainerUB.selfDeploy();
		});

		__horizVertSetup.setup([this](ContextStateManager& stateMgr)
		{
			TextureContainerUniformInterface& texContainerInterface = __texContainerUB.getInterface();
			texContainerInterface.textures = { 0, __pBloomColorAttachment2->getHandle() };
			__texContainerUB.selfDeploy();
		});

		__compositionSetup.setup([this](ContextStateManager& stateMgr)
		{
			TextureContainerUniformInterface& texContainerInterface = __texContainerUB.getInterface();
			texContainerInterface.textures = { 0, __pOriginalColorAttachment->getHandle() };
			texContainerInterface.textures = { 1, __pBloomColorAttachment1->getHandle() };
			__texContainerUB.selfDeploy();
		});
	}

	void BloomPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__basicSetup();

		// 1. color extraction
		__colorExtractionSetup();
		__pBloomFrameBuffer1->bind();
		__extractionProgram.bind();
		__fullscreenDrawer.draw();

		// 2. horizontal blur
		__horizBlurSetup();
		__pBloomFrameBuffer2->bind();
		__blurHorizProgram.bind();
		__fullscreenDrawer.draw();

		// 3. vertical blur
		__horizVertSetup();
		__pBloomFrameBuffer1->bind();
		__blurVertProgram.bind();
		__fullscreenDrawer.draw();

		// 4. composition
		__compositionSetup();
		renderTarget.bind();
		__compositionProgram.bind();
		__fullscreenDrawer.draw();
	}

	void BloomPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__pOriginalColorAttachment = _getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::LINEAR, TextureMagFilterValue::LINEAR, 0ULL);

		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pOriginalColorAttachment);

		if (__attachDepthBuffer)
		{
			__pDepthStencilAttachment =
				_getRenderBuffer(width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

			_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
		}


		__pBloomColorAttachment1 = _getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::LINEAR, TextureMagFilterValue::LINEAR, 1ULL);

		__pBloomFrameBuffer1->attach(AttachmentType::COLOR_ATTACHMENT0, *__pBloomColorAttachment1);


		__pBloomColorAttachment2 = _getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::LINEAR, TextureMagFilterValue::LINEAR, 2ULL);

		__pBloomFrameBuffer2->attach(AttachmentType::COLOR_ATTACHMENT0, *__pBloomColorAttachment2);
	}
}