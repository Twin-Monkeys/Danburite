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
	BloomPostProcessor::BloomPostProcessor() :
		__bloomSetter(UniformBufferFactory::getInstance().getUniformBuffer(ShaderIdentifier::Name::UniformBuffer::BLOOM)),
		__pBloomFrameBuffer(make_unique<FrameBuffer>()),
		__extractionProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_COLOR_EXTRACTION)),
		__blurHorizProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_COLOR_EXTRACTION)),
		__blurVertProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_COLOR_EXTRACTION)),
		__compositionProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_COMPOSITION)),
		__pOriginalColorAttachment(make_unique<AttachableTexture2D>()),
		__pBloomColorAttachment(make_unique<AttachableTexture2D>()),
		__pDepthStencilAttachment(make_unique<RenderBuffer>())
	{
		__pOriginalColorAttachment->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		__pOriginalColorAttachment->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		__pOriginalColorAttachment->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pOriginalColorAttachment->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);

		__pBloomColorAttachment->setState(TextureParamType::TEXTURE_WRAP_S, TextureWrapValue::CLAMP_TO_EDGE);
		__pBloomColorAttachment->setState(TextureParamType::TEXTURE_WRAP_T, TextureWrapValue::CLAMP_TO_EDGE);
		__pBloomColorAttachment->setState(TextureParamType::TEXTURE_MIN_FILTER, TextureMinFilterValue::LINEAR);
		__pBloomColorAttachment->setState(TextureParamType::TEXTURE_MAG_FILTER, TextureMagFilterValue::LINEAR);
	}

	void BloomPostProcessor::_onRender(UniformBuffer &attachmentSetter, VertexArray &fullscreenQuadVA) noexcept
	{
		PostProcessor *const pBoundProcessor = _getBoundProcessor();

		__bloomSetter.setUniformFloat(
			ShaderIdentifier::Name::Bloom::BRIGHTNESS_THRESHOLD, __brightnessThreshold);

		__pBloomFrameBuffer->bind();

		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT_ARRAY[0],
			TextureUtil::getHandleIfExist(__pOriginalColorAttachment));

		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT_ARRAY[1],
			TextureUtil::getHandleIfExist(__pBloomColorAttachment));

		// 1. color extraction
		__extractionProgram.bind();
		fullscreenQuadVA.draw();

		// 2. horizontal blur
		__blurHorizProgram.bind();
		fullscreenQuadVA.draw();

		// 3. vertical blur
		__blurVertProgram.bind();
		fullscreenQuadVA.draw();

		// 4. composition
		pBoundProcessor->bind();
		__compositionProgram.bind();
		fullscreenQuadVA.draw();
	}

	void BloomPostProcessor::setScreenSize(const GLsizei width, const GLsizei height) noexcept
	{
		__pOriginalColorAttachment->memoryAlloc(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB);

		__pBloomColorAttachment->memoryAlloc(
			width, height, TextureInternalFormatType::RGB16F, TextureExternalFormatType::RGB);

		__pDepthStencilAttachment->memoryAlloc(
			width, height, RenderBufferInternalFormatType::DEPTH24_STENCIL8);

		__pBloomFrameBuffer->attach(AttachmentType::COLOR_ATTACHMENT0, *__pBloomColorAttachment);

		_attach(AttachmentType::COLOR_ATTACHMENT0, *__pOriginalColorAttachment);
		_attach(AttachmentType::DEPTH_STENCIL_ATTACHMENT, *__pDepthStencilAttachment);
	}
}