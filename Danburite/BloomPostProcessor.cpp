#include "BloomPostProcessor.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	BloomPostProcessor::BloomPostProcessor(const bool attachDepthBuffer) :
		__attachDepthBuffer(attachDepthBuffer),
		__bloomSetter(UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::BLOOM)),
		__pBloomFrameBuffer1(make_unique<FrameBuffer>()),
		__pBloomFrameBuffer2(make_unique<FrameBuffer>()),
		__extractionProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_COLOR_EXTRACTION)),
		__blurHorizProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_BLUR_HORIZ)),
		__blurVertProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_BLUR_VERT)),
		__compositionProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_COMPOSITION)),
		__texContainerSetter(UniformBufferFactory::getInstance().
			getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::TEX_CONTAINER)),

		__fullscreenDrawer(FullscreenDrawer::getInstance())
	{
		__basicSetup.setSetupFunction([this](ContextStateManager& stateMgr)
		{
			__bloomSetter.setUniformFloat(
				ShaderIdentifier::Name::Bloom::BRIGHTNESS_THRESHOLD, __brightnessThreshold);

			__bloomSetter.setUniformFloat(
				ShaderIdentifier::Name::Bloom::EFFECT_STRENGTH, __effectStrength);

			stateMgr.setState(GLStateType::DEPTH_TEST, false);
			stateMgr.setState(GLStateType::STENCIL_TEST, false);
			stateMgr.setState(GLStateType::BLEND, false);
			stateMgr.setState(GLStateType::CULL_FACE, true);

			stateMgr.setCulledFace(FacetType::BACK);
			stateMgr.setFrontFace(WindingOrderType::COUNTER_CLOCKWISE);
		});

		__colorExtractionSetup.setSetupFunction([this](ContextStateManager& stateMgr)
		{
			__texContainerSetter.setUniformUvec2(
				ShaderIdentifier::Name::Attachment::TEX0, __pOriginalColorAttachment->getHandle());
		});

		__horizBlurSetup.setSetupFunction([this](ContextStateManager& stateMgr)
		{
			__texContainerSetter.setUniformUvec2(
				ShaderIdentifier::Name::Attachment::TEX0, __pBloomColorAttachment1->getHandle());
		});

		__horizVertSetup.setSetupFunction([this](ContextStateManager& stateMgr)
		{
			__texContainerSetter.setUniformUvec2(
				ShaderIdentifier::Name::Attachment::TEX0, __pBloomColorAttachment2->getHandle());
		});

		__compositionSetup.setSetupFunction([this](ContextStateManager& stateMgr)
		{
			__texContainerSetter.setUniformUvec2(
				ShaderIdentifier::Name::Attachment::TEX0, __pOriginalColorAttachment->getHandle());

			__texContainerSetter.setUniformUvec2(
				ShaderIdentifier::Name::Attachment::TEX1, __pBloomColorAttachment1->getHandle());
		});
	}

	void BloomPostProcessor::render(FrameBuffer &renderTarget) noexcept
	{
		__basicSetup.setup();

		// 1. color extraction
		__colorExtractionSetup.setup();
		__pBloomFrameBuffer1->bind();
		__extractionProgram.bind();
		__fullscreenDrawer.draw();

		// 2. horizontal blur
		__horizBlurSetup.setup();
		__pBloomFrameBuffer2->bind();
		__blurHorizProgram.bind();
		__fullscreenDrawer.draw();

		// 3. vertical blur
		__horizVertSetup.setup();
		__pBloomFrameBuffer1->bind();
		__blurVertProgram.bind();
		__fullscreenDrawer.draw();

		// 4. composition
		__compositionSetup.setup();
		renderTarget.bind();
		__compositionProgram.bind();
		__fullscreenDrawer.draw();
	}

	void BloomPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__pOriginalColorAttachment = _getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 0ULL);

		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pOriginalColorAttachment);

		if (__attachDepthBuffer)
		{
			__pDepthStencilAttachment =
				_getRenderBuffer(width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

			_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
		}


		__pBloomColorAttachment1 = _getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 1ULL);

		__pBloomFrameBuffer1->attach(AttachmentType::COLOR_ATTACHMENT0, *__pBloomColorAttachment1);


		__pBloomColorAttachment2 = _getTexRectangle(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB,
			TextureDataType::FLOAT, TextureMinFilterValue::NEAREST, TextureMagFilterValue::NEAREST, 2ULL);

		__pBloomFrameBuffer2->attach(AttachmentType::COLOR_ATTACHMENT0, *__pBloomColorAttachment2);
	}
}