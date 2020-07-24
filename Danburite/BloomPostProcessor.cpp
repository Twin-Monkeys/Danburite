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
		__compositionProgram(ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_COMPOSITION))
	{}

	void BloomPostProcessor::_onRender(
		PostProcessor* const pBoundProcessor,
		UniformBuffer &attachmentSetter, VertexArray &fullscreenQuadVA) noexcept
	{
		__bloomSetter.setUniformFloat(
			ShaderIdentifier::Name::Bloom::BRIGHTNESS_THRESHOLD, __brightnessThreshold);

		__bloomSetter.setUniformFloat(
			ShaderIdentifier::Name::Bloom::EFFECT_STRENGTH, __effectStrength);

		// 1. color extraction
		__pBloomFrameBuffer1->bind();

		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT0, __pOriginalColorAttachment->getHandle());

		__extractionProgram.bind();
		fullscreenQuadVA.draw();

		// 2. horizontal blur
		__pBloomFrameBuffer2->bind();

		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT0, __pBloomColorAttachment1->getHandle());

		__blurHorizProgram.bind();
		fullscreenQuadVA.draw();

		// 3. vertical blur
		__pBloomFrameBuffer1->bind();

		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT0, __pBloomColorAttachment2->getHandle());

		__blurVertProgram.bind();
		fullscreenQuadVA.draw();

		// 4. composition
		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT0, __pOriginalColorAttachment->getHandle());

		attachmentSetter.setUniformUvec2(
			ShaderIdentifier::Name::Attachment::COLOR_ATTACHMENT1, __pBloomColorAttachment1->getHandle());

		if (pBoundProcessor)
			pBoundProcessor->bind();
		else
			PostProcessor::unbind();

		__compositionProgram.bind();
		fullscreenQuadVA.draw();
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