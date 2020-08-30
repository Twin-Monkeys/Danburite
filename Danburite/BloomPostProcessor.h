#pragma once

#include "PostProcessor.h"
#include "ProgramFactory.h"
#include "UniformBufferFactory.h"
#include "DeferredUniformBuffer.h"
#include "BloomUniformInterface.h"
#include "TextureContainerUniformInterface.h"
#include "ShaderIdentifier.h"
#include "AttachableTextureRectangle.h"
#include "RenderBuffer.h"
#include "Constant.h"
#include "FullscreenDrawer.h"
#include "SetupTransaction.h"

namespace Danburite
{
	class BloomPostProcessor : public PostProcessor
	{
	private:
		DeferredUniformBuffer<BloomUniformInterface> &__bloomUB =
			UniformBufferFactory::getInstance().getUniformBuffer<BloomUniformInterface>();

		DeferredUniformBuffer<TextureContainerUniformInterface> &__texContainerUB =
			UniformBufferFactory::getInstance().getUniformBuffer<TextureContainerUniformInterface>();

		ObjectGL::Program &__extractionProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_COLOR_EXTRACTION);

		ObjectGL::Program &__blurHorizProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_BLUR_HORIZ);

		ObjectGL::Program &__blurVertProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_BLUR_VERT);

		ObjectGL::Program &__compositionProgram =
			ProgramFactory::getInstance().getProgram(ProgramType::POST_PROCESS_BLOOM_COMPOSITION);

		FullscreenDrawer &__fullscreenDrawer = FullscreenDrawer::getInstance();

		const bool __attachDepthBuffer;

		float __brightnessThreshold = Constant::Bloom::DEFAULT_BRIGHTNESS_THRESHOLD;
		float __effectStrength = Constant::Bloom::DEFAULT_EFFECT_STRENGTH;

		std::unique_ptr<ObjectGL::FrameBuffer> __pBloomFrameBuffer1 = std::make_unique<ObjectGL::FrameBuffer>();
		std::unique_ptr<ObjectGL::FrameBuffer> __pBloomFrameBuffer2 = std::make_unique<ObjectGL::FrameBuffer>();
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pOriginalColorAttachment;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pBloomColorAttachment1;
		std::shared_ptr<ObjectGL::AttachableTextureRectangle> __pBloomColorAttachment2;
		std::shared_ptr<ObjectGL::RenderBuffer> __pDepthStencilAttachment;

		SetupTransaction __basicSetup;
		SetupTransaction __colorExtractionSetup;
		SetupTransaction __horizBlurSetup;
		SetupTransaction __horizVertSetup;
		SetupTransaction __compositionSetup;

	protected:
		virtual void render(ObjectGL::FrameBuffer &renderTarget) noexcept override;

	public:
		BloomPostProcessor(const bool attachDepthBuffer = false);

		constexpr float getBrightnessThreshold() const noexcept;
		constexpr void setBrightnessThreshold(const float threshold) noexcept;

		constexpr float getEffectStrength() const noexcept;
		constexpr void setEffectStrength(const float strength) noexcept;

		virtual void setScreenSize(const GLsizei width, const GLsizei height) noexcept override;

		virtual ~BloomPostProcessor() = default;
	};

	constexpr float BloomPostProcessor::getBrightnessThreshold() const noexcept
	{
		return __brightnessThreshold;
	}

	constexpr void BloomPostProcessor::setBrightnessThreshold(const float threshold) noexcept
	{
		__brightnessThreshold = threshold;
	}

	constexpr float BloomPostProcessor::getEffectStrength() const noexcept
	{
		return __effectStrength;
	}

	constexpr void BloomPostProcessor::setEffectStrength(const float strength) noexcept
	{
		__effectStrength = strength;
	}
}