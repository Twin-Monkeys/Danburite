#include "BloomPostProcessor.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "ShaderIdentifier.h"
#include "TextureUtil.h"

using namespace std;
using namespace glm;
using namespace ObjectGL;

namespace Danburite
{
	BloomPostProcessor::BloomPostProcessor(const bool attachDepthBuffer) :
		__bloomSetter(UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::BLOOM)),
		__pBloomFrameBuffer1(make_unique<FrameBuffer>()),
		__pBloomFrameBuffer2(make_unique<FrameBuffer>()),
		__extractionProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_COLOR_EXTRACTION)),
		__blurHorizProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_BLUR_HORIZ)),
		__blurVertProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_BLUR_VERT)),
		__compositionProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_COMPOSITION))
	{
		__initColorAttachment();

		if (attachDepthBuffer)
			__pDepthStencilAttachment = make_unique<RenderBuffer>();
	}

	void BloomPostProcessor::__initColorAttachment() noexcept
	{
		__pOriginalColorAttachment = make_unique<AttachableTexture2D>();
		__pOriginalColorAttachment->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		__pOriginalColorAttachment->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		__pOriginalColorAttachment->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pOriginalColorAttachment->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);

		__pBloomColorAttachment1 = make_unique<AttachableTexture2D>();
		__pBloomColorAttachment1->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		__pBloomColorAttachment1->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		__pBloomColorAttachment1->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pBloomColorAttachment1->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);

		__pBloomColorAttachment2 = make_unique<AttachableTexture2D>();
		__pBloomColorAttachment2->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		__pBloomColorAttachment2->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		__pBloomColorAttachment2->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pBloomColorAttachment2->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	}

	void BloomPostProcessor::_onRender(UniformBuffer &attachmentSetter, VertexArray &fullscreenQuadVA) noexcept
	{
 		PostProcessor *const pBoundProcessor = _getBoundProcessor();

		__bloomSetter.setUniformFloat(
			ShaderIdentifier::Name::Bloom::BRIGHTNESS_THRESHOLD, __brightnessThreshold);

		// 1. color extraction
		__pBloomFrameBuffer1->bind();

		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT0,
			TextureUtil::getHandleIfExist(__pOriginalColorAttachment));

		__extractionProgram.bind();
		fullscreenQuadVA.draw();

		// 2. horizontal blur
		__pBloomFrameBuffer2->bind();

		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT0,
			TextureUtil::getHandleIfExist(__pBloomColorAttachment1));

		__blurHorizProgram.bind();
		fullscreenQuadVA.draw();

		// 3. vertical blur
		__pBloomFrameBuffer1->bind();

		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT0,
			TextureUtil::getHandleIfExist(__pBloomColorAttachment2));

		__blurVertProgram.bind();
		fullscreenQuadVA.draw();

		// 4. composition
		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT0,
			TextureUtil::getHandleIfExist(__pOriginalColorAttachment));

		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT1,
			TextureUtil::getHandleIfExist(__pBloomColorAttachment1));

		if (pBoundProcessor)
			pBoundProcessor->bind();
		else
			PostProcessor::unbind();

		__compositionProgram.bind();
		fullscreenQuadVA.draw();
	}

	void BloomPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		if (__pOriginalColorAttachment->isHandleCreated())
			__initColorAttachment();

		__pOriginalColorAttachment->memoryAlloc(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB);
		
		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pOriginalColorAttachment);

		if (__pDepthStencilAttachment)
		{
			__pDepthStencilAttachment->memoryAlloc(
				width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

			_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
		}

		__pBloomColorAttachment1->memoryAlloc(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB);

		__pBloomFrameBuffer1->attach(AttachmentType::COLOR_ATTACHMENT0, *__pBloomColorAttachment1);

		__pBloomColorAttachment2->memoryAlloc(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB);

		__pBloomFrameBuffer2->attach(AttachmentType::COLOR_ATTACHMENT0, *__pBloomColorAttachment2);
	}
}